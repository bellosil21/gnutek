#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Spectrum Analyzer
# Generated: Tue Dec 22 21:37:46 2020
##################################################


if __name__ == '__main__':
    import ctypes
    import sys
    if sys.platform.startswith('linux'):
        try:
            x11 = ctypes.cdll.LoadLibrary('libX11.so')
            x11.XInitThreads()
        except:
            print "Warning: failed to XInitThreads()"

from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio import wxgui
from gnuradio.eng_option import eng_option
from gnuradio.fft import window
from gnuradio.filter import firdes
from gnuradio.wxgui import fftsink2
from gnuradio.wxgui import forms
from grc_gnuradio import wxgui as grc_wxgui
from optparse import OptionParser
import TekRSA
import wx


class top_block2(grc_wxgui.top_block_gui):

    def __init__(self):
        grc_wxgui.top_block_gui.__init__(self, title="Spectrum Analyzer")
        _icon_path = "/usr/share/icons/hicolor/32x32/apps/gnuradio-grc.png"
        self.SetIcon(wx.Icon(_icon_path, wx.BITMAP_TYPE_ANY))

        ##################################################
        # Variables
        ##################################################
        self.samp_rate = samp_rate = 3.5e6
        self.gain = gain = 5
        self.CF = CF = 94e6

        ##################################################
        # Blocks
        ##################################################
        _gain_sizer = wx.BoxSizer(wx.VERTICAL)
        self._gain_text_box = forms.text_box(
        	parent=self.GetWin(),
        	sizer=_gain_sizer,
        	value=self.gain,
        	callback=self.set_gain,
        	label='Gain',
        	converter=forms.float_converter(),
        	proportion=0,
        )
        self._gain_slider = forms.slider(
        	parent=self.GetWin(),
        	sizer=_gain_sizer,
        	value=self.gain,
        	callback=self.set_gain,
        	minimum=0,
        	maximum=35,
        	num_steps=35,
        	style=wx.SL_HORIZONTAL,
        	cast=float,
        	proportion=1,
        )
        self.Add(_gain_sizer)
        _CF_sizer = wx.BoxSizer(wx.VERTICAL)
        self._CF_text_box = forms.text_box(
        	parent=self.GetWin(),
        	sizer=_CF_sizer,
        	value=self.CF,
        	callback=self.set_CF,
        	label='center frequency',
        	converter=forms.float_converter(),
        	proportion=0,
        )
        self._CF_slider = forms.slider(
        	parent=self.GetWin(),
        	sizer=_CF_sizer,
        	value=self.CF,
        	callback=self.set_CF,
        	minimum=70e6,
        	maximum=135e6,
        	num_steps=15,
        	style=wx.SL_HORIZONTAL,
        	cast=float,
        	proportion=1,
        )
        self.Add(_CF_sizer)
        self.wxgui_fftsink2_1 = fftsink2.fft_sink_c(
        	self.GetWin(),
        	baseband_freq=CF,
        	y_per_div=10,
        	y_divs=10,
        	ref_level=-40,
        	ref_scale=2.0,
        	sample_rate=samp_rate,
        	fft_size=1024,
        	fft_rate=15,
        	average=False,
        	avg_alpha=None,
        	title='FFT Plot',
        	peak_hold=False,
        	win=window.hamming,
        )
        self.Add(self.wxgui_fftsink2_1.win)
        self.blocks_multiply_const_vxx_0 = blocks.multiply_const_vcc((gain, ))
        self.TekRSA_iq_stream_0 = TekRSA.iq_stream(CF, -20, 2e6, 1000000, 0)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.TekRSA_iq_stream_0, 0), (self.blocks_multiply_const_vxx_0, 0))
        self.connect((self.blocks_multiply_const_vxx_0, 0), (self.wxgui_fftsink2_1, 0))

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.wxgui_fftsink2_1.set_sample_rate(self.samp_rate)

    def get_gain(self):
        return self.gain

    def set_gain(self, gain):
        self.gain = gain
        self._gain_slider.set_value(self.gain)
        self._gain_text_box.set_value(self.gain)
        self.blocks_multiply_const_vxx_0.set_k((self.gain, ))

    def get_CF(self):
        return self.CF

    def set_CF(self, CF):
        self.CF = CF
        self._CF_slider.set_value(self.CF)
        self._CF_text_box.set_value(self.CF)
        self.wxgui_fftsink2_1.set_baseband_freq(self.CF)
        self.TekRSA_iq_stream_0.set_cf(self.CF)


def main(top_block_cls=top_block2, options=None):

    tb = top_block_cls()
    tb.Start(True)
    tb.Wait()


if __name__ == '__main__':
    main()