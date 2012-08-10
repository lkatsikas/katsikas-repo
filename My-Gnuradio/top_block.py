#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Top Block
# Generated: Fri Aug 10 15:57:39 2012
##################################################

from PyQt4 import Qt
from gnuradio import digital
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.gr import firdes
from gnuradio.qtgui import qtgui
from grc_gnuradio import blks2 as grc_blks2
from optparse import OptionParser
import sip
import sys

class top_block(gr.top_block, Qt.QWidget):

	def __init__(self):
		gr.top_block.__init__(self, "Top Block")
		Qt.QWidget.__init__(self)
		self.setWindowTitle("Top Block")
		self.setWindowIcon(Qt.QIcon.fromTheme('gnuradio-grc'))
		self.top_scroll_layout = Qt.QVBoxLayout()
		self.setLayout(self.top_scroll_layout)
		self.top_scroll = Qt.QScrollArea()
		self.top_scroll.setFrameStyle(Qt.QFrame.NoFrame)
		self.top_scroll_layout.addWidget(self.top_scroll)
		self.top_scroll.setWidgetResizable(True)
		self.top_widget = Qt.QWidget()
		self.top_scroll.setWidget(self.top_widget)
		self.top_layout = Qt.QVBoxLayout(self.top_widget)
		self.top_grid_layout = Qt.QGridLayout()
		self.top_layout.addLayout(self.top_grid_layout)


		##################################################
		# Variables
		##################################################
		self.samp_rate = samp_rate = 32000

		##################################################
		# Blocks
		##################################################
		self.qtgui_sink_x_0 = qtgui.sink_c(
			512, #fftsize
			firdes.WIN_BLACKMAN_hARRIS, #wintype
			0, #fc
			256, #bw
			"QT GUI Plot", #name
			True, #plotfreq
			False, #plotwaterfall
			False, #plottime
			True, #plotconst
		)
		self._qtgui_sink_x_0_win = sip.wrapinstance(self.qtgui_sink_x_0.pyqwidget(), Qt.QWidget)
		self.top_layout.addWidget(self._qtgui_sink_x_0_win)
		self.gr_file_source_0 = gr.file_source(gr.sizeof_char*1, "/home/katsikas/katsikas-repo/My-Gnuradio/Common/Korgialas_GeiaSou.ts", True)
		self.gr_file_sink_0 = gr.file_sink(gr.sizeof_char*1, "/home/katsikas/katsikas-repo/My-Gnuradio/Common/Results.ts")
		self.gr_file_sink_0.set_unbuffered(False)
		self.digital_ofdm_mod_0 = grc_blks2.packet_mod_b(digital.ofdm_mod(
				options=grc_blks2.options(
					modulation="bpsk",
					fft_length=512,
					occupied_tones=50,
					cp_length=1,
					pad_for_usrp=True,
					log=None,
					verbose=None,
				),
			),
			payload_length=0,
		)
		self.digital_ofdm_demod_0 = grc_blks2.packet_demod_b(digital.ofdm_demod(
				options=grc_blks2.options(
					modulation="bpsk",
					fft_length=512,
					occupied_tones=50,
					cp_length=1,
					snr=100,
					log=None,
					verbose=None,
				),
				callback=lambda ok, payload: self.digital_ofdm_demod_0.recv_pkt(ok, payload),
			),
		)

		##################################################
		# Connections
		##################################################
		self.connect((self.gr_file_source_0, 0), (self.digital_ofdm_mod_0, 0))
		self.connect((self.digital_ofdm_mod_0, 0), (self.digital_ofdm_demod_0, 0))
		self.connect((self.digital_ofdm_demod_0, 0), (self.gr_file_sink_0, 0))
		self.connect((self.digital_ofdm_mod_0, 0), (self.qtgui_sink_x_0, 0))

	def get_samp_rate(self):
		return self.samp_rate

	def set_samp_rate(self, samp_rate):
		self.samp_rate = samp_rate

if __name__ == '__main__':
	parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
	(options, args) = parser.parse_args()
	qapp = Qt.QApplication(sys.argv)
	tb = top_block()
	tb.start()
	tb.show()
	qapp.exec_()
	tb.stop()

