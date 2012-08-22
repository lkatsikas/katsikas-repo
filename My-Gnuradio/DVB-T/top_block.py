#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Top Block
# Generated: Wed Aug 22 19:46:59 2012
##################################################

from PyQt4 import Qt
from gnuradio import digital
from gnuradio import eng_notation
from gnuradio import gr
from gnuradio import uhd
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
		self.samp_rate = samp_rate = (68/7.0)*1000000
		self.occupied = occupied = 1704

		##################################################
		# Blocks
		##################################################
		self.uhd_usrp_source_0 = uhd.usrp_source(
			device_addr="addr=192.168.10.2",
			stream_args=uhd.stream_args(
				cpu_format="fc32",
				channels=range(1),
			),
		)
		self.uhd_usrp_source_0.set_samp_rate(samp_rate)
		self.uhd_usrp_source_0.set_center_freq(474000000, 0)
		self.uhd_usrp_source_0.set_gain(20, 0)
		self.uhd_usrp_source_0.set_antenna("RX2", 0)
		self.uhd_usrp_source_0.set_bandwidth(8000000, 0)
		self.uhd_usrp_sink_0 = uhd.usrp_sink(
			device_addr="addr=192.168.10.2",
			stream_args=uhd.stream_args(
				cpu_format="fc32",
				channels=range(1),
			),
		)
		self.uhd_usrp_sink_0.set_samp_rate(samp_rate)
		self.uhd_usrp_sink_0.set_center_freq(474000000, 0)
		self.uhd_usrp_sink_0.set_gain(10, 0)
		self.uhd_usrp_sink_0.set_antenna("TX/RX", 0)
		self.uhd_usrp_sink_0.set_bandwidth(8000000, 0)
		self.qtgui_time_sink_x_0 = qtgui.time_sink_c(
			1024, #size
			samp_rate, #bw
			"QT GUI Plot", #name
			1 #number of inputs
		)
		self._qtgui_time_sink_x_0_win = sip.wrapinstance(self.qtgui_time_sink_x_0.pyqwidget(), Qt.QWidget)
		self.top_layout.addWidget(self._qtgui_time_sink_x_0_win)
		self.qtgui_sink_x_0 = qtgui.sink_c(
			2048, #fftsize
			firdes.WIN_BLACKMAN_hARRIS, #wintype
			0, #fc
			8000000, #bw
			"QT GUI Plot", #name
			True, #plotfreq
			False, #plotwaterfall
			False, #plottime
			True, #plotconst
		)
		self._qtgui_sink_x_0_win = sip.wrapinstance(self.qtgui_sink_x_0.pyqwidget(), Qt.QWidget)
		self.top_layout.addWidget(self._qtgui_sink_x_0_win)
		self.qtgui_ofdm_vector_analyzer_x_0 = qtgui.ofdm_vector_analyzer_c(
			  1704, #occupied_tones
			  "qpsk" #modulation
			  )
		self._qtgui_ofdm_vector_analyzer_x_0_win = sip.wrapinstance(self.qtgui_ofdm_vector_analyzer_x_0.pyqwidget(), Qt.QWidget)
		self.top_grid_layout.addWidget(self._qtgui_ofdm_vector_analyzer_x_0_win, 
		   )
		self.gr_vector_to_stream_0 = gr.vector_to_stream(gr.sizeof_gr_complex*1, occupied)
		self.gr_multiply_const_vxx_0 = gr.multiply_const_vcc((0.4882, ))
		self.gr_file_source_0 = gr.file_source(gr.sizeof_char*1, "/home/katsikas/katsikas-repo/My-Gnuradio/Common/Text.txt", True)
		self.gr_file_sink_0 = gr.file_sink(gr.sizeof_char*1, "/home/katsikas/Desktop/sink.txt")
		self.gr_file_sink_0.set_unbuffered(False)
		self.digital_ofdm_mod_0 = grc_blks2.packet_mod_b(digital.ofdm_mod(
				options=grc_blks2.options(
					modulation="qpsk",
					fft_length=2048,
					occupied_tones=occupied,
					cp_length=128,
					pad_for_usrp=True,
					log=None,
					verbose=None,
				),
			),
			payload_length=0,
		)
		self.digital_ofdm_demod_0 = grc_blks2.packet_demod_b(digital.ofdm_demod(
				options=grc_blks2.options(
					modulation="qpsk",
					fft_length=2048,
					occupied_tones=occupied,
					cp_length=128,
					snr=10,
					show_vector_analyzer="yes",
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
		self.connect((self.digital_ofdm_demod_0, 0), (self.gr_file_sink_0, 0))
		self.connect((self.gr_multiply_const_vxx_0, 0), (self.qtgui_sink_x_0, 0))
		self.connect((self.gr_multiply_const_vxx_0, 0), (self.uhd_usrp_sink_0, 0))
		self.connect((self.digital_ofdm_demod_0, 1), (self.gr_vector_to_stream_0, 0))
		self.connect((self.gr_vector_to_stream_0, 0), (self.qtgui_ofdm_vector_analyzer_x_0, 0))
		self.connect((self.digital_ofdm_mod_0, 0), (self.gr_multiply_const_vxx_0, 0))
		self.connect((self.gr_multiply_const_vxx_0, 0), (self.qtgui_time_sink_x_0, 0))
		self.connect((self.uhd_usrp_source_0, 0), (self.digital_ofdm_demod_0, 0))

	def get_samp_rate(self):
		return self.samp_rate

	def set_samp_rate(self, samp_rate):
		self.samp_rate = samp_rate
		self.uhd_usrp_source_0.set_samp_rate(self.samp_rate)
		self.uhd_usrp_sink_0.set_samp_rate(self.samp_rate)

	def get_occupied(self):
		return self.occupied

	def set_occupied(self, occupied):
		self.occupied = occupied

if __name__ == '__main__':
	parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
	(options, args) = parser.parse_args()
	qapp = Qt.QApplication(sys.argv)
	tb = top_block()
	tb.start()
	tb.show()
	qapp.exec_()
	tb.stop()

