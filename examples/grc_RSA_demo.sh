script_dir="$(CDPATH= cd -- $(dirname -- $0) && pwd)"
export LD_LIBRARY_PATH=/opt/lib
ldconfig
#gnuradio-companion "${script_dir}/frequency_sink.grc"
gnuradio-companion "${script_dir}/fm_radio.grc"
