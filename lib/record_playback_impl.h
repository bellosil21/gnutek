/* 
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

#ifndef INCLUDED_TEKRSA_RECORD_PLAYBACK_IMPL_H
#define INCLUDED_TEKRSA_RECORD_PLAYBACK_IMPL_H

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>

#include <TekRSA/record_playback.h>
#include "RSA_API.h"
#include <queue>
#include <string>

#include <TekRSA/record_playback.h>

namespace gr {
  namespace TekRSA {

    class record_playback_impl : public record_playback
    {

     public:
      record_playback_impl(const char* in_f_base, int in_dsk_md, int in_f_suf,  const char* in_sv_path, 
		int in_out_cfg, int in_en);
      ~record_playback_impl();
      virtual void set_diskfile_mode(RSA_API::StreamingMode mode);
      virtual void set_file_savepath(const char *path);
      virtual void set_file_basename(const char *base);
      virtual void set_file_suffix(int suffixCtl);
      virtual void set_enable(bool enabled);
      virtual void set_output_config(RSA_API::IFSOUTDEST fout);

      // Where all the action really happens
 	int work(int noutput_items,
	       gr_vector_const_void_star &input_items,
	       gr_vector_void_star &output_items);
    };

  } // namespace TekRSA
} // namespace gr

#endif /* INCLUDED_TEKRSA_RECORD_PLAYBACK_H */

