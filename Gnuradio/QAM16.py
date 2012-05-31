#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: QAM16
# Author: katsikas
# Generated: Fri May 25 18:32:03 2012
##################################################

from gnuradio import digital
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio import uhd
from gnuradio.eng_option import eng_option
from gnuradio.gr import firdes
from grc_gnuradio import blks2 as grc_blks2
from grc_gnuradio import wxgui as grc_wxgui
from optparse import OptionParser
import wx

class QAM16(grc_wxgui.top_block_gui):

	def __init__(self):
		grc_wxgui.top_block_gui.__init__(self, title="QAM16")

		##################################################
		# Variables
		##################################################
		self.samp_rate = samp_rate = 44100

		##################################################
		# Blocks
		##################################################
		self.uhd_usrp_sink_0 = uhd.usrp_sink(
			device_addr="addr=192.168.10.2",
			stream_args=uhd.stream_args(
				cpu_format="fc32",
				channels=range(1),
			),
		)
		self.uhd_usrp_sink_0.set_samp_rate(samp_rate)
		self.uhd_usrp_sink_0.set_center_freq(474e6, 0)
		self.uhd_usrp_sink_0.set_gain(15, 0)
		self.gr_wavfile_source_0 = gr.wavfile_source("/home/katsikas/guitarup_full.wav", True)
		self.gr_wavfile_sink_0 = gr.wavfile_sink("/home/katsikas/katsikas-repo/Gnuradio/Sent.wav", 1, samp_rate, 8)
		self.gr_throttle_0_0 = gr.throttle(gr.sizeof_float*1, samp_rate)
		self.digital_ofdm_mod_0 = grc_blks2.packet_mod_f(digital.ofdm_mod(
				options=grc_blks2.options(
					modulation="qam64",
					fft_length=512,
					occupied_tones=256,
					cp_length=128,
					pad_for_usrp=True,
					log=None,
					verbose=None,
				),
			),
			payload_length=0,
		)
		self.digital_ofdm_demod_0 = grc_blks2.packet_demod_f(digital.ofdm_demod(
				options=grc_blks2.options(
					modulation="qam16",
					fft_length=512,
					occupied_tones=256,
					cp_length=128,
					snr=10,
					log=None,
					verbose=None,
				),
				callback=lambda ok, payload: self.digital_ofdm_demod_0.recv_pkt(ok, payload),
			),
		)

		##################################################
		# Connections
		##################################################
		self.connect((self.gr_wavfile_source_0, 0), (self.gr_throttle_0_0, 0))
		self.connect((self.digital_ofdm_mod_0, 0), (self.uhd_usrp_sink_0, 0))
		self.connect((self.gr_throttle_0_0, 0), (self.digital_ofdm_mod_0, 0))
		self.connect((self.digital_ofdm_mod_0, 0), (self.digital_ofdm_demod_0, 0))
		self.connect((self.digital_ofdm_demod_0, 0), (self.gr_wavfile_sink_0, 0))

	def get_samp_rate(self):
		return self.samp_rate

	def set_samp_rate(self, samp_rate):
		self.samp_rate = samp_rate
		self.uhd_usrp_sink_0.set_samp_rate(self.samp_rate)

if __name__ == '__main__':
	parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
	(options, args) = parser.parse_args()
	tb = QAM16()
	tb.Run(True)

