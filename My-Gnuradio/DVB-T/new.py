#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: QAM16
# Author: katsikas
# Generated: Sat Jun 16 13:42:53 2012
##################################################

from PyQt4 import Qt
from gnuradio import gr
from gnuradio import digital
##################################################                    
#------------------------------------------------#
from gnuradio import dvbt
#from gnuradio import dvbt_swig
#------------------------------------------------#
##################################################
from gnuradio import eng_notation
from gnuradio.eng_option import eng_option
from grc_gnuradio import blks2 as grc_blks2
from gnuradio.gr import firdes
from optparse import OptionParser
from gnuradio.qtgui import qtgui
import PyQt4.Qwt5 as Qwt
import sys
import sip
import math
import random

class QAM16(gr.top_block, Qt.QWidget):

	def __init__(self):
		gr.top_block.__init__(self, "QAM")
		Qt.QWidget.__init__(self)
		self.setWindowTitle("QAM")
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
		self.variable_qtgui_range_0 = variable_qtgui_range_0 = 474e6
		self.samp_rate = samp_rate = 44100
		self.Useful_Carriers = Useful_Carriers = 1704
		self.Transmission_Frequency = Transmission_Frequency = 474e6
		self.OFDM_Symbols = OFDM_Symbols = 2048
		self.Guard_Interval = Guard_Interval = 4
		self.Gain = Gain = 20
		self.Modulation_Type = "qpsk"
		self.SNR = 20
		data_length=10000


		##################################################
		# Blocks
		##################################################
		self._variable_qtgui_range_0_layout = Qt.QVBoxLayout()
		self._variable_qtgui_range_0_tool_bar = Qt.QToolBar(self)
		self._variable_qtgui_range_0_layout.addWidget(self._variable_qtgui_range_0_tool_bar)
		self._variable_qtgui_range_0_tool_bar.addWidget(Qt.QLabel("Transmission_Frequency"+": "))
		self._variable_qtgui_range_0_counter = Qwt.QwtCounter()
		self._variable_qtgui_range_0_counter.setRange(470e6, 478e6, 1e3)
		self._variable_qtgui_range_0_counter.setNumButtons(2)
		self._variable_qtgui_range_0_counter.setValue(self.variable_qtgui_range_0)
		self._variable_qtgui_range_0_tool_bar.addWidget(self._variable_qtgui_range_0_counter)
		self._variable_qtgui_range_0_counter.valueChanged.connect(self.set_variable_qtgui_range_0)
		self._variable_qtgui_range_0_slider = Qwt.QwtSlider(None, Qt.Qt.Horizontal, Qwt.QwtSlider.BottomScale, Qwt.QwtSlider.BgSlot)
		self._variable_qtgui_range_0_slider.setRange(470e6, 478e6, 1e3)
		self._variable_qtgui_range_0_slider.setValue(self.variable_qtgui_range_0)
		self._variable_qtgui_range_0_slider.setMinimumWidth(200)
		self._variable_qtgui_range_0_slider.valueChanged.connect(self.set_variable_qtgui_range_0)
		self._variable_qtgui_range_0_layout.addWidget(self._variable_qtgui_range_0_slider)
		self.top_layout.addLayout(self._variable_qtgui_range_0_layout)
		self.qtgui_sink_x_0 = qtgui.sink_c(
			OFDM_Symbols, #fftsize
			firdes.WIN_BLACKMAN_hARRIS, #wintype
			Transmission_Frequency, #fc
			8e6, #bw
			"QT GUI Plot", #name
			False, #plotfreq
			False, #plotwaterfall
			False, #plottime
			True, #plotconst
		)
		self._qtgui_sink_x_0_win = sip.wrapinstance(self.qtgui_sink_x_0.pyqwidget(), Qt.QWidget)
		self.top_layout.addWidget(self._qtgui_sink_x_0_win)

		################################################################################################################
                #--------------------------------------------------------------------------------------------------------------#
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
		self.stream = gr.vector_to_stream(gr.sizeof_char, 1)
                self.vector = gr.stream_to_vector(gr.sizeof_char, 1)
		#--------------------------------------------------------------------------------------------------------------#
		################################################################################################################

		"""
		self.connect((self.src, 0), (self.pack, 0))
                self.connect((self.pack, 0), (self.bytes2chunks, 0))
                self.connect((self.bytes2chunks, 0), (self.chunks2symbols, 0))
		self.connect((self.chunks2symbols,0), (self.qtgui_sink_x_0,0))
                self.connect((self.chunks2symbols,0), (self.decoder,0))
                self.connect((self.decoder,0), (self.unpack,0))
                self.connect((self.unpack,0), (self.snk,0))
		"""

		self.digital_ofdm_mod_0 = grc_blks2.packet_mod_b(digital.dvbt_ofdm_mod(
                                options=grc_blks2.options(
                                        modulation=self.Modulation_Type,
                                        fft_length=OFDM_Symbols,
                                        occupied_tones=Useful_Carriers,
                                        cp_length=OFDM_Symbols/Guard_Interval,
                                        pad_for_usrp=True,
                                        log=None,
                                        verbose=None,
                                ),
                        ),
                        payload_length=0,
                )
		self.digital_ofdm_demod_0 = grc_blks2.packet_demod_b(digital.dvbt_ofdm_demod(
                                options=grc_blks2.options(
                                        modulation=self.Modulation_Type,
                                        fft_length=OFDM_Symbols,
                                        occupied_tones=Useful_Carriers,
                                        cp_length=OFDM_Symbols/Guard_Interval,
                                        snr=self.SNR,
                                        log=None,
                                        verbose=None,
                                ),
                                callback=lambda ok, payload: self.digital_ofdm_demod_0.recv_pkt(ok, payload),
                        ),
                )
		
		self.connect((self.src, 0), (self.stream, 0))
		self.connect((self.stream, 0), (self.digital_ofdm_mod_0, 0))
		self.connect((self.digital_ofdm_mod_0,0), (self.qtgui_sink_x_0,0))
		self.connect((self.digital_ofdm_mod_0,0), (self.digital_ofdm_demod_0,0))
		self.connect((self.digital_ofdm_demod_0, 0), (self.vector,0))
		self.connect((self.vector, 0), (self.snk,0))

		errors = 0
                for i, j in zip(data, self.snk.data()):
                        if i != j:
                                errors += 1

                print("\nBER = {0}".format(1.0*errors/data_length))


	def get_variable_qtgui_range_0(self):
		return self.variable_qtgui_range_0

	def set_variable_qtgui_range_0(self, variable_qtgui_range_0):
		self.variable_qtgui_range_0 = variable_qtgui_range_0
		self._variable_qtgui_range_0_counter.setValue(self.variable_qtgui_range_0)
		self._variable_qtgui_range_0_slider.setValue(self.variable_qtgui_range_0)

	def get_samp_rate(self):
		return self.samp_rate

	def set_samp_rate(self, samp_rate):
		self.samp_rate = samp_rate

	def get_Useful_Carriers(self):
		return self.Useful_Carriers

	def set_Useful_Carriers(self, Useful_Carriers):
		self.Useful_Carriers = Useful_Carriers

	def get_Transmission_Frequency(self):
		return self.Transmission_Frequency

	def set_Transmission_Frequency(self, Transmission_Frequency):
		self.Transmission_Frequency = Transmission_Frequency

	def get_OFDM_Symbols(self):
		return self.OFDM_Symbols

	def set_OFDM_Symbols(self, OFDM_Symbols):
		self.OFDM_Symbols = OFDM_Symbols

	def get_Guard_Interval(self):
		return self.Guard_Interval

	def set_Guard_Interval(self, Guard_Interval):
		self.Guard_Interval = Guard_Interval

	def get_Gain(self):
		return self.Gain

	def set_Gain(self, Gain):
		self.Gain = Gain

if __name__ == '__main__':
	parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
	(options, args) = parser.parse_args()
	qapp = Qt.QApplication(sys.argv)
	tb = QAM16()
	tb.start()
	tb.show()
	qapp.exec_()
	tb.stop()

