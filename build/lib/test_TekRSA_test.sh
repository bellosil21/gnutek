#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/tekgnu/gnutek/lib
export GR_CONF_CONTROLPORT_ON=False
export PATH=/home/tekgnu/gnutek/build/lib:$PATH
export LD_LIBRARY_PATH=/home/tekgnu/gnutek/build/lib:$LD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH
test-TekRSA 
