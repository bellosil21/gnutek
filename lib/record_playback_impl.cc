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
		int in_out_cfg, int in_en)
    {
      return gnuradio::get_initial_sptr
        (new record_playback_impl(in_f_base,in_dsk_md,in_f_suf,in_sv_path,
			    in_out_cfg, in_en));
    }

    /*
     * The private constructor,gets and sets device settings
     */
    record_playback_impl::record_playback_impl(const char* in_f_base, int in_dsk_md,
				   int in_f_suf, const char* in_sv_path, int in_out_cfg, int in_en)
      : gr::sync_block("record_playback",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(1, 1, sizeof(gr_complex)))
    {

    }

  } /* namespace rsa507 */
} /* namespace gr */


