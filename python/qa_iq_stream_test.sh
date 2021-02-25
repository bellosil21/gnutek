#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/tekgnu/gnutek/python
export GR_CONF_CONTROLPORT_ON=False
export PATH=/home/tekgnu/gnutek/python:$PATH
export LD_LIBRARY_PATH=/home/tekgnu/gnutek/lib:$LD_LIBRARY_PATH
export PYTHONPATH=/home/tekgnu/gnutek/swig:$PYTHONPATH
/usr/bin/python2 /home/tekgnu/gnutek/python/qa_iq_stream.py 
