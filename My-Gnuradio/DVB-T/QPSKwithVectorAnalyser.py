#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Top Block
# Generated: Thu Aug  9 17:12:43 2012
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
import random

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
		self.Useful_Carriers = Useful_Carriers = 1704
		self.OFDM_Symbols = OFDM_Symbols = 2048
		self.Guard_Interval = Guard_Interval = 16
		data_length=1000

		##################################################
		# Blocks
		##################################################
		self.qtgui_sink_x_0 = qtgui.sink_c(
			1024, #fftsize
			firdes.WIN_BLACKMAN_hARRIS, #wintype
			0, #fc
			samp_rate, #bw
			"QT GUI Plot", #name
			False, #plotfreq
			False, #plotwaterfall
			False, #plottime
			True, #plotconst
		)
		self._qtgui_sink_x_0_win = sip.wrapinstance(self.qtgui_sink_x_0.pyqwidget(), Qt.QWidget)
		self.top_layout.addWidget(self._qtgui_sink_x_0_win)
		self.gr_file_source_0 = gr.file_source(gr.sizeof_char*1, "/home/katsikas/katsikas-repo/My-Gnuradio/Common/Text.txt", False)
		self.gr_file_sink_0 = gr.file_sink(gr.sizeof_char*1, "/home/katsikas/katsikas-repo/My-Gnuradio/Common/Results.txt")
		self.gr_file_sink_0.set_unbuffered(False)

		#########################################################################################
		#											#
		#########################################################################################
		points = [1+1j, 1-1j, -1+1j, -1-1j]
    		constellation = digital.constellation_dvbt_qpsk().base()
		data = tuple([random.randint(0,1) for i in range(0, data_length)])
    		self.src = gr.vector_source_b(data)
    		self.pack = gr.unpacked_to_packed_bb(1, gr.GR_MSB_FIRST)
    		self.bytes2chunks = gr.packed_to_unpacked_bb(constellation.bits_per_symbol(),
                                            gr.GR_MSB_FIRST)

    		print constellation.points()
		#print constellation.bits_per_symbol()
    		#print constellation.pre_diff_code()

    		self.chunks2symbols = gr.chunks_to_symbols_bc(constellation.points())    
    		self.decoder = digital.constellation_decoder_cb(constellation)
    		self.unpack = gr.unpack_k_bits_bb(constellation.bits_per_symbol())
    		self.snk = gr.vector_sink_b()
    		self.connect(self.src, self.pack, self.bytes2chunks, (self.chunks2symbols,0))
		self.connect((self.chunks2symbols,0), (self.qtgui_sink_x_0,0))
    		self.connect(self.chunks2symbols, self.decoder, self.unpack, self.snk)

    		errors = 0
    		for i, j in zip(data, self.snk.data()):
        		if i != j:
            			errors += 1

		print("\nBER = {0}".format(1.0*errors/data_length))

		##################################################
		# Connections
		##################################################
		"""
		self.connect((self.digital_ofdm_mod_0, 0), (self.digital_ofdm_demod_0, 0))
		self.connect((self.digital_ofdm_mod_0, 0), (self.qtgui_sink_x_0, 0))
		self.connect((self.gr_file_source_0, 0), (self.digital_ofdm_mod_0, 0))
		self.connect((self.digital_ofdm_demod_0, 0), (self.gr_file_sink_0, 0))
		"""

	def get_samp_rate(self):
		return self.samp_rate

	def set_samp_rate(self, samp_rate):
		self.samp_rate = samp_rate
		self.qtgui_sink_x_0.set_frequency_range(0, self.samp_rate)

	def get_Useful_Carriers(self):
		return self.Useful_Carriers

	def set_Useful_Carriers(self, Useful_Carriers):
		self.Useful_Carriers = Useful_Carriers

	def get_OFDM_Symbols(self):
		return self.OFDM_Symbols

	def set_OFDM_Symbols(self, OFDM_Symbols):
		self.OFDM_Symbols = OFDM_Symbols

	def get_Guard_Interval(self):
		return self.Guard_Interval

	def set_Guard_Interval(self, Guard_Interval):
		self.Guard_Interval = Guard_Interval

if __name__ == '__main__':
	parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
	(options, args) = parser.parse_args()
	qapp = Qt.QApplication(sys.argv)
	tb = top_block()
	tb.start()
	tb.show()
	qapp.exec_()
	tb.stop()

