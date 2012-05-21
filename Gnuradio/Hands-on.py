#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Top Block
# Generated: Tue May 15 20:42:49 2012
##################################################

from gnuradio import audio
from gnuradio import digital
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.gr import firdes
from grc_gnuradio import blks2 as grc_blks2
from grc_gnuradio import wxgui as grc_wxgui
from optparse import OptionParser
import wx

class top_block(grc_wxgui.top_block_gui):

	def __init__(self):
		grc_wxgui.top_block_gui.__init__(self, title="Top Block")

		##################################################
		# Variables
		##################################################
		self.samp_rate = samp_rate = 44100

		##################################################
		# Blocks
		##################################################
		self.gr_wavfile_source_0 = gr.wavfile_source("/home/katsikas/guitarup_full.wav", False)
		self.gr_wavfile_sink_0 = gr.wavfile_sink("/home/katsikas/katsikas-repo/Gnuradio/Sent.wav", 1, samp_rate, 8)
		self.gr_throttle_0 = gr.throttle(gr.sizeof_float*1, samp_rate)
		self.digital_ofdm_mod_0 = grc_blks2.packet_mod_f(digital.ofdm_mod(
				options=grc_blks2.options(
					modulation="qam16",
					fft_length=2048,
					occupied_tones=200,
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
					fft_length=2048,
					occupied_tones=200,
					cp_length=128,
					snr=10,
					log=None,
					verbose=None,
				),
				callback=lambda ok, payload: self.digital_ofdm_demod_0.recv_pkt(ok, payload),
			),
		)

		################################## My code  #####################################		
		# self.audio_sink_0 = audio.sink (samp_rate, "")				#	
		# self.connect((self.digital_ofdm_demod_0, 0), (self.audio_sink_0, 0))  	#
		# self.connect((self.digital_ofdm_demod_0, 0), (self.gr_wavfile_sink_0, 0)) 	#
		#################################################################################

		##################################################
		# Connections
		##################################################
		self.connect((self.digital_ofdm_mod_0, 0), (self.digital_ofdm_demod_0, 0))
		self.connect((self.gr_wavfile_source_0, 0), (self.gr_throttle_0, 0))
		self.connect((self.gr_throttle_0, 0), (self.digital_ofdm_mod_0, 0))

	def get_samp_rate(self):
		return self.samp_rate

	def set_samp_rate(self, samp_rate):
		self.samp_rate = samp_rate

if __name__ == '__main__':
	tb = top_block()
	# print "python re mounia";
	tb.Run(True)

