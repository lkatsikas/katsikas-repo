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
import PyQt4.Qwt5 as Qwt
import sys

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
		self.Useful_Carriers = Useful_Carriers = 1024
		self.Transmission_Frequency = Transmission_Frequency = 474e6
		self.OFDM_Symbols = OFDM_Symbols = 2048
		self.Guard_Interval = Guard_Interval = 4
		self.Gain = Gain = 20

		################################################################################################################
		#--------------------------------------------------------------------------------------------------------------#
		self.input = '/home/katsikas/katsikas-repo/My-Gnuradio/Common/Korgialas_GeiaSou.ts'
		self.output = '/home/katsikas/katsikas-repo/My-Gnuradio/Common/Results.ts'
		#self.input = '/home/katsikas/katsikas-repo/My-Gnuradio/Common/Text.txt'
                #self.output = '/home/katsikas/katsikas-repo/My-Gnuradio/Common/Results.txt'
		self.temp = '/home/katsikas/katsikas-repo/My-Gnuradio/Common/dump.txt'
		#--------------------------------------------------------------------------------------------------------------#

		#--------------------------------------------------------------------------------------------------------------#
                #self.gr_file_source_0 = gr.file_source(gr.sizeof_char*1, self.input, False)
                with open(self.input, 'rb'):
                        self.gr_file_source_0 = dvbt.dvbt_source(self.input)

                #self.gr_file_sink_0 = gr.file_sink(gr.sizeof_char*1, self.output)
                #self.gr_file_sink_0.set_unbuffered(False)
                with open(self.output, 'rb'):
                        self.gr_file_sink_0 = dvbt.dvbt_sink(self.output)

                #self.gr_file_sink_1 = gr.file_sink(gr.sizeof_char*1, self.temp)
                #self.gr_file_sink_1.set_unbuffered(False)
                with open(self.temp, 'rb'):
                        self.gr_file_sink_1 = gr.file_sink(gr.sizeof_char*1, self.temp)
                self.stream = gr.vector_to_stream(gr.sizeof_char, 256)
                self.vector = gr.stream_to_vector(gr.sizeof_char, 256)
                #--------------------------------------------------------------------------------------------------------------#

		#--------------------------------------------------------------------------------------------------------------#
		self.randomizer = dvbt.randomizer()
                self.derandomizer = dvbt.derandomizer()

		self.rs_encoder = dvbt.rs_encoder()
		self.rs_decoder = dvbt.rs_decoder()
	
		self.interleaver = dvbt.interleaver()
		self.deinterleaver = dvbt.deinterleaver()
		#self.trellis_encoder = dvbt.trellis_encoder()
		#self.viterbi_decoder = dvbt.viterbi_decoder()
		self.delay = gr.delay(gr.sizeof_char*1*256, 204)
		#--------------------------------------------------------------------------------------------------------------#
		################################################################################################################


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

		################################################################################################################
		#--------------------------------------------------------------------------------------------------------------#
		self.digital_ofdm_mod_0 = grc_blks2.packet_mod_b(digital.ofdm_mod(
                                options=grc_blks2.options(
                                        modulation="qpsk",
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
                self.digital_ofdm_demod_0 = grc_blks2.packet_demod_b(digital.ofdm_demod(
                                options=grc_blks2.options(
                                        modulation="qpsk",
                                        fft_length=OFDM_Symbols,
                                        occupied_tones=Useful_Carriers,
                                        cp_length=OFDM_Symbols/Guard_Interval,
                                        snr=20,
                                        log=None,
                                        verbose=None,
                                ),
                                callback=lambda ok, payload: self.digital_ofdm_demod_0.recv_pkt(ok, payload),
                        ),
                )

		#--------------------------------------------------------------------------------------------------------------#
		################################################################################################################
		


		##################################################
		# Connections
		##################################################
		################################################################################################################
                #--------------------------------------------------------------------------------------------------------------#		
		self.connect((self.gr_file_source_0, 0), (self.randomizer, 0))
		self.connect((self.randomizer, 0), (self.rs_encoder, 0))
                self.connect((self.rs_encoder, 0), (self.interleaver, 0))
                self.connect((self.interleaver, 0),(self.stream, 0))
		self.connect((self.stream, 0), (self.gr_file_sink_1, 0))
		self.connect((self.stream, 0), (self.digital_ofdm_mod_0, 0))
		self.connect((self.digital_ofdm_mod_0, 0), (self.digital_ofdm_demod_0, 0))
		self.connect((self.digital_ofdm_demod_0, 0), (self.vector, 0))
		self.connect((self.vector, 0), (self.deinterleaver, 0))
                self.connect((self.deinterleaver, 0), (self.rs_decoder, 0))
                self.connect((self.rs_decoder, 0), (self.derandomizer, 0))
		self.connect((self.derandomizer, 0), (self.gr_file_sink_0, 0))
	
		
		
		"""
                self.connect((self.gr_file_source_0, 0), (self.randomizer, 0))
                self.connect((self.randomizer, 0), (self.rs_encoder, 0))
		self.connect((self.rs_encoder, 0), (self.interleaver, 0))
		self.connect((self.interleaver, 0),(self.stream, 0))
                self.connect((self.stream, 0), (self.gr_file_sink_1, 0))
		self.connect((self.stream, 0), (self.vector, 0))	
                self.connect((self.vector, 0), (self.deinterleaver, 0))
		#self.connect((self.deinterleaver, 0), (self.delay, 0))
		#self.connect((self.delay, 0), (self.rs_decoder, 0))		
		self.connect((self.deinterleaver, 0), (self.rs_decoder, 0))
		self.connect((self.rs_decoder, 0), (self.derandomizer, 0))
                self.connect((self.derandomizer, 0), (self.gr_file_sink_0, 0))
		"""


		"""	
		self.connect((self.gr_file_source_0, 0), (self.randomizer, 0))
                self.connect((self.randomizer, 0), (self.rs_encoder, 0))
                self.connect((self.rs_encoder, 0), (self.interleaver, 0))
		self.connect((self.interleaver, 0),(self.trellis_encoder, 0))
                self.connect((self.trellis_encoder, 0),(self.viterbi_decoder, 0))
                self.connect((self.viterbi_decoder, 0), (self.deinterleaver, 0))
                self.connect((self.deinterleaver, 0), (self.rs_decoder, 0))
                self.connect((self.rs_decoder, 0), (self.derandomizer, 0))
                self.connect((self.derandomizer, 0), (self.gr_file_sink_0, 0))
		"""         
		#--------------------------------------------------------------------------------------------------------------#
                ################################################################################################################


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

