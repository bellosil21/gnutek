#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Top Block
# Generated: Thu Feb 25 11:08:25 2021
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

from gnuradio import analog
from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import filter
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


class top_block(grc_wxgui.top_block_gui):

    def __init__(self):
        grc_wxgui.top_block_gui.__init__(self, title="Top Block")
        _icon_path = "/usr/share/icons/hicolor/32x32/apps/gnuradio-grc.png"
        self.SetIcon(wx.Icon(_icon_path, wx.BITMAP_TYPE_ANY))

        ##################################################
        # Variables
        ##################################################
        self.sr = sr = 3.5e6
        self.tw = tw = 10000
        self.samp_rate = samp_rate = sr
        self.rl = rl = -20
        self.gain = gain = 1
        self.co = co = 100000
        self.cf = cf = 100.3e6
        self.bw = bw = 2e6

        ##################################################
        # Blocks
        ##################################################
        self._gain_chooser = forms.drop_down(
        	parent=self.GetWin(),
        	value=self.gain,
        	callback=self.set_gain,
        	label='gain',
        	choices=[0.2, 0.4, 0.6, 0.8, 1, 1.5, 2, 2.5, 3, 3.5],
        	labels=[1, 2, 3, 4, 5, 6, 7, 8, 9, 10],
        )
        self.Add(self._gain_chooser)
        _cf_sizer = wx.BoxSizer(wx.VERTICAL)
        self._cf_text_box = forms.text_box(
        	parent=self.GetWin(),
        	sizer=_cf_sizer,
        	value=self.cf,
        	callback=self.set_cf,
        	label='cf',
        	converter=forms.float_converter(),
        	proportion=0,
        )
        self._cf_slider = forms.slider(
        	parent=self.GetWin(),
        	sizer=_cf_sizer,
        	value=self.cf,
        	callback=self.set_cf,
        	minimum=88.5e6,
        	maximum=108.5e6,
        	num_steps=100,
        	style=wx.SL_HORIZONTAL,
        	cast=float,
        	proportion=1,
        )
        self.Add(_cf_sizer)
        self.wxgui_fftsink2_0 = fftsink2.fft_sink_c(
        	self.GetWin(),
        	baseband_freq=cf,
        	y_per_div=10,
        	y_divs=10,
        	ref_level=0,
        	ref_scale=2.0,
        	sample_rate=samp_rate,
        	fft_size=1024,
        	fft_rate=15,
        	average=False,
        	avg_alpha=None,
        	title='Sample_Bandpass',
        	peak_hold=False,
        	win=window.hamming,
        )
        self.Add(self.wxgui_fftsink2_0.win)
        self.rational_resampler_xxx_0 = filter.rational_resampler_fff(
                interpolation=441,
                decimation=2500,
                taps=None,
                fractional_bw=None,
        )
        self.low_pass_filter_0 = filter.fir_filter_ccf(int(samp_rate/250000), firdes.low_pass(
        	4, samp_rate, co, tw, firdes.WIN_HAMMING, 6.76))
        self.blocks_wavfile_sink_0 = blocks.wavfile_sink('sample.wav', 1, 44100, 8)
        self.blocks_throttle_0 = blocks.throttle(gr.sizeof_gr_complex*1, samp_rate,True)
        self.blocks_multiply_const_vxx_0 = blocks.multiply_const_vff((gain, ))
        self.analog_wfm_rcv_0 = analog.wfm_rcv(
        	quad_rate=250000,
        	audio_decimation=1,
        )
        self.analog_agc_xx_0 = analog.agc_ff(1e-4, 1.0, 1.0)
        self.analog_agc_xx_0.set_max_gain(65536)
        self.TekRSA_iq_stream_0_0 = TekRSA.iq_stream(cf, rl, bw, 1000000, 0)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.TekRSA_iq_stream_0_0, 0), (self.blocks_throttle_0, 0))
        self.connect((self.TekRSA_iq_stream_0_0, 0), (self.wxgui_fftsink2_0, 0))
        self.connect((self.analog_agc_xx_0, 0), (self.blocks_multiply_const_vxx_0, 0))
        self.connect((self.analog_wfm_rcv_0, 0), (self.rational_resampler_xxx_0, 0))
        self.connect((self.blocks_multiply_const_vxx_0, 0), (self.blocks_wavfile_sink_0, 0))
        self.connect((self.blocks_throttle_0, 0), (self.low_pass_filter_0, 0))
        self.connect((self.low_pass_filter_0, 0), (self.analog_wfm_rcv_0, 0))
        self.connect((self.rational_resampler_xxx_0, 0), (self.analog_agc_xx_0, 0))

    def get_sr(self):
        return self.sr

    def set_sr(self, sr):
        self.sr = sr
        self.set_samp_rate(self.sr)

    def get_tw(self):
        return self.tw

    def set_tw(self, tw):
        self.tw = tw
        self.low_pass_filter_0.set_taps(firdes.low_pass(4, self.samp_rate, self.co, self.tw, firdes.WIN_HAMMING, 6.76))

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.wxgui_fftsink2_0.set_sample_rate(self.samp_rate)
        self.low_pass_filter_0.set_taps(firdes.low_pass(4, self.samp_rate, self.co, self.tw, firdes.WIN_HAMMING, 6.76))
        self.blocks_throttle_0.set_sample_rate(self.samp_rate)

    def get_rl(self):
        return self.rl

    def set_rl(self, rl):
        self.rl = rl
        self.TekRSA_iq_stream_0_0.set_rl(self.rl)

    def get_gain(self):
        return self.gain

    def set_gain(self, gain):
        self.gain = gain
        self._gain_chooser.set_value(self.gain)
        self.blocks_multiply_const_vxx_0.set_k((self.gain, ))

    def get_co(self):
        return self.co

    def set_co(self, co):
        self.co = co
        self.low_pass_filter_0.set_taps(firdes.low_pass(4, self.samp_rate, self.co, self.tw, firdes.WIN_HAMMING, 6.76))

    def get_cf(self):
        return self.cf

    def set_cf(self, cf):
        self.cf = cf
        self._cf_slider.set_value(self.cf)
        self._cf_text_box.set_value(self.cf)
        self.wxgui_fftsink2_0.set_baseband_freq(self.cf)
        self.TekRSA_iq_stream_0_0.set_cf(self.cf)

    def get_bw(self):
        return self.bw

    def set_bw(self, bw):
        self.bw = bw
        self.TekRSA_iq_stream_0_0.set_bw(self.bw)


def main(top_block_cls=top_block, options=None):

    tb = top_block_cls()
    tb.Start(True)
    tb.Wait()


if __name__ == '__main__':
    main()
