/* -*- c++ -*- */
/* 
 * Copyright 2017 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 3, or (at your
 * option) any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#include <gnuradio/io_signature.h>
#include "RSA_API.h"
#include "record_playback_impl.h"

namespace gr {
  namespace TekRSA {

void set_diskfile_mode(RSA_API::StreamingMode mode);
void set_file_savepath(const char *path);
void set_file_basename(const char *base);
void set_file_suffix(int suffixCtl);
void set_enable(bool enabled);
void set_output_config(RSA_API::IFSOUTDEST fout);
static bool return_check(const char* tag, RSA_API::ReturnStatus rs);
static bool search_and_connect(int, bool);
static bool connect_to_hw_and_setup(int, bool);
static bool stop_and_disconnect();
static bool run_alignment();
static bool can_run = true;

static bool search_and_connect(int dev_sel, bool do_reset)
{
	RSA_API::ReturnStatus rs;

	printf("\nSearching for Devices...");
	int num_dev;
	int* dev_id;
	const char** dev_sn;
	const char** dev_type;
	rs = RSA_API::DEVICE_SearchInt(&num_dev,&dev_id, &dev_sn,&dev_type);
	if (!return_check("DEVICE_Search", rs))
		return false;

	printf("Number of Devices found: %i\n", num_dev);
	if (num_dev == 0)
		return false;

	int use_dev = -1;
	if (dev_type[dev_sel] != NULL)
	{
		use_dev=dev_sel;
		printf("Found user specified device: %s.\n",
			dev_type[dev_sel]);
	}
	else
	{
		printf("Invalid device ID was entered..Finding all valid devices.\n");
		for (int n = 0; n<num_dev; n++)
		{
			// display connected devices
			printf("Dev: %i, ID: %i, S/N: \"%s\", ", n, dev_id[n], dev_sn[n]);
			printf("Type: \"%s\"\n", dev_type[n]);
			std::string this_string = dev_type[n];
			//should allow us to see any RSA's, not working
			//if (this_string.substr(0,3) == "RSA") 
			{
				printf("Found first valid device: %s, will use this.\n",dev_type[n]);
				use_dev=n;
				break;
			}
		}
	}

	//select device
	int id = use_dev;

	//for manual dev# usage
	//int dev_id = dev_id[dev_sel];

	if (do_reset)    // if requested, reset the device and reconnect
	{
		printf("Resetting device: %d... ", id);
		rs = RSA_API::DEVICE_Reset(id);
		if (!return_check("DEVICE_Reset", rs))
			return false;
		printf("Successful\n");
	}

	printf("Connecting to device\n");
	rs = RSA_API::DEVICE_Connect(id);
	if (!return_check("DEVICE_Connect", rs))
	{
		printf("Failed on DEVICE_Connect(), please exit the program.");
		return false;   // failed to connect
	}
	printf("Successful connection to %s!\n",dev_type[id]);

	rs = RSA_API::CONFIG_Preset();  // preset device to initial state
	if (!return_check("CONFIG_Preset", rs))
		return false;

	// Print the device SW/FW/HW info

	RSA_API::DEVICE_INFO dev_info;
	rs = RSA_API::DEVICE_GetInfo(&dev_info);
	if (!return_check("DEVICE_GetInfo", rs))
		return false;
	printf("Prod:%s  SN:%s  HW:%s  FX3:%s  FPGA:%s  API:%s\n", 
		dev_info.nomenclature, dev_info.serialNum, dev_info.hwVersion,
		dev_info.fwVersion, dev_info.fpgaVersion, dev_info.apiVersion);

	//enables auto-attentuation and RF Preamp for 5xx-6xx series
	if (dev_info.nomenclature[3] == '5' || dev_info.nomenclature[3] == '6') //5 and 6 for 5xx and 6xx series
	{
		printf("Enabling 5xx-6xx Unique Settings Master.");
		
		bool enable_rsa = true;
		rs = RSA_API::CONFIG_SetAutoAttenuationEnable(&enable_rsa);
		if(!return_check("CONFIG_SetAutoAttentuationEnable", rs))
			return false;
		bool enable_preamp = false;
		rs = RSA_API::CONFIG_SetRFPreampEnable(&enable_preamp);
		if(!return_check("CONFIG_SetRFPreampEnable", rs))
			return false;
	}

	return true;
}

static bool connect_to_hw_and_setup(int dev, bool align)
{
	//search and connect to device via usb
	if (!search_and_connect(dev, align))
		return false;
	/*
	//alignment
	bool needsAlignment;
	RSA_API::ALIGN_GetAlignmentNeeded(&needsAlignment);
	printf("\nAlignment Needed: %s\n", needsAlignment ? "Yes" : "No");
	

	if (needsAlignment)
	{
		if (!RunAlignment())
		{
			printf("Alignment failed\n");
			return false;
		}
	}
	printf("\nAlignment complete!\n");
	*/
	return true;
}

/*
 * RunAlignment
 * Runs alignment for RSA via device API
 */
static bool RunAlignment()
{
	printf("Alignment: Running, please wait...");
	RSA_API::ReturnStatus rs = RSA_API::ALIGN_RunAlignment();
	if (!return_check("ALIGN_RunAlignment", rs))
		return false;
	return true;
}

/*
 * stop_and_disconnect
 * Stops running mode on RSA, disconnects it
 * Reports run statistics if flagged
 */
static bool stop_and_disconnect()
{
	RSA_API::ReturnStatus rs; 
#ifdef RSA_API_V2_OLD
	RSA_API::run_mode run_mode;
	RSA_API::GetRunState(&run_mode);
	RSA_API::IQSTREAM_Stop(); //stop streaming/writing to output file
	if (run_mode == RSA_API::running)     // if running, stop
#else
	bool is_running;
	RSA_API::DEVICE_GetEnable(&is_running);
	if (is_running)     // if running, stop
#endif
	{
		printf("Stopping Device...\n");
		rs = RSA_API::DEVICE_Stop();
		if (!return_check("DEVICE_Stop", rs))
			return false;
	}

	printf("Disconnecting from Device...\n");
	rs = RSA_API::DEVICE_Disconnect();      // disconnect from device
	if (!return_check("DEVICE_Disconnect", rs))
		return false;

	return true;
}

// Translate Rtn status and print string
static bool return_check(const char* tag, RSA_API::ReturnStatus rs)
{
        bool pass = (rs == RSA_API::noError);

        RSA_API_DLL const char* GetErrorString(RSA_API::ReturnStatus status);
        if (!pass)
        {
                printf("%s: %s: %i:\"%s\"\n", tag,
                        (pass ? "" : "FAILURE"),
                        (int)rs, RSA_API::DEVICE_GetErrorString(rs));
        }
        return pass;
}

void record_playback_impl::set_diskfile_mode(RSA_API::StreamingMode mode)
{
        RSA_API::ReturnStatus rs;

        rs = RSA_API::IFSTREAM_SetDiskFileMode(mode);
        if (!return_check("IFSTREAM_SetDiskFileMode", rs))
        {
                return;
        }
        return;
}

void record_playback_impl::set_file_suffix(int suffixCtl)
{
        RSA_API::ReturnStatus rs;

        rs = RSA_API::IFSTREAM_SetDiskFilenameSuffix(suffixCtl);
        if (!return_check("IFSTREAM_SetDiskFilenameSuffix", rs))
        {
                return;
        }
        return;
}


void record_playback_impl::set_file_savepath(const char *path)
{
        RSA_API::ReturnStatus rs;

        rs = RSA_API::IFSTREAM_SetDiskFilePath(path);
        if (!return_check("IFSTREAM_SetDiskFilePath", rs))
        {
                return;
        }
        return;
}

void record_playback_impl::set_file_basename(const char *base)
{
        RSA_API::ReturnStatus rs;

        rs = RSA_API::IFSTREAM_SetDiskFilenameBase(base);
        if (!return_check("IFSTREAM_SetDiskFilenameBase", rs))
        {
                return;
        }
        return;
}

void record_playback_impl::set_enable(bool enabled)
{
        RSA_API::ReturnStatus rs;

        rs = RSA_API::IFSTREAM_SetEnable(enabled);
        if (!return_check("IFSTREAM_SetEnabled", rs))
        {
                return;
        }
        return;
}

void record_playback_impl::set_output_config(RSA_API::IFSOUTDEST fout)
{
        RSA_API::ReturnStatus rs;

        rs = RSA_API::IFSTREAM_SetOutputConfiguration(fout);
        if (!return_check("IFSTREAM_SetOutputConfiguration", rs))
        {
                return;
        }
        return;
}

//GNU radio funcs
    record_playback::sptr
    record_playback::make(const char* in_f_base, int in_dsk_md, int in_f_suf,  const char* in_sv_path, 
		int in_out_cfg, int in_en, int in_dev_id)
    {
      return gnuradio::get_initial_sptr
        (new record_playback_impl(in_f_base,in_dsk_md,in_f_suf,in_sv_path,
			    in_out_cfg, in_en));
    }

    /*
     * The private constructor,gets and sets device settings
     */
    record_playback_impl::record_playback_impl(const char* in_f_base, int in_dsk_md,
				   int in_f_suf, const char* in_sv_path, int in_out_cfg, int in_en,
				   int in_dev_id)
      : gr::sync_block("record_playback",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1, 1, sizeof(gr_complex)))
    {
	RSA_API::ReturnStatus rs;
	const char* f_base = (const char*) in_f_base;
        int dsk_md = (int) in_dsk_md;
	int f_suf = (int) in_f_suf;
        const char* sv_path = (const char*) in_sv_path;
        int out_cfg = (int) in_out_cfg;
	int en = (int) in_en;

	//Collect and set all RSA configs
	bool reboot = false;
	if (!connect_to_hw_and_setup(dev_id, reboot))
	{
		printf("Failed on connect_to_hw_and_setup...\n");
		can_run = false;
	}

	if (can_run)
	{
           // Print app build date/time and API version
		char api_version[200];
		RSA_API::DEVICE_GetAPIVersion(api_version);
	        
		RSA_API::IFSTREAM_SetOutputConfiguration(IFSOD_FILE_R3F);
		RSA_API::IFSTREAM_SetDiskFileMode(StreamingModeFramed);
		RSA_API::IFSTREAM_SetFileNameBase("test");
		RSA_API::IFSTREAM_SetFileDiskFileNameSuffix(IQSSDFN_SUFFIX_TIMESTAMP);
                RSA_API::IFSTREAM_SetDiskFileLength(1000);
		RSA_API::IFSTREAM_SetDiskFileCount(10);
		RSA_API::IFSTREAM_SetEnable(true);
	}
    }

    /*
     * Our virtual destructor.
     */
    record_playback_impl::~record_playback_impl()
    {
	RSA_API::SetEnable(false);
	RSA_API::IFSTREAM_SetOutputConfiguration(IFSOD_CLIENT);
	stop_and_disconnect();
    }

    int
    record_playback_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {

    }


  } /* namespace rsa507 */
} /* namespace gr */


