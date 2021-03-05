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

#ifndef INCLUDED_TEKRSA_RECORD_PLAYBACK_H
#define INCLUDED_TEKRSA_RECORD_PLAYBACK_H

#include <TekRSA/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace TekRSA {

    class TEKRSA_API record_playback : virtual public gr::sync_block
    {

     public:
      typedef boost::shared_ptr<record_playback> sptr;
      virtual void set_diskfile_mode(RSA_API::StreamingMode mode) = 0;
      virtual void set_file_savepath(const char *path) = 0;
      virtual void set_file_basename(const char *base) = 0;
      virtual void set_file_suffix(int suffixCtl) = 0;
      virtual void set_enable(bool enabled) = 0;
      virtual void set_output_config(RSA_API::IFSOUTDEST fout) = 0;

      // Where all the action really happens
      static sptr make(const char* in_f_base, int in_dsk_md, int in_f_suf,  const char* in_sv_path, int in_out_cfg, int in_en, int in_dev_id);
    };

  } // namespace TekRSA
} // namespace gr

#endif /* INCLUDED_TEKRSA_RECORD_PLAYBACK_H */

