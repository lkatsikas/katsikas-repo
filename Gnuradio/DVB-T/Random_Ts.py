#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: QAM16
# Author: katsikas
# Generated: Sun Jun 10 19:30:31 2012
##################################################

from PyQt4 import Qt
from gnuradio import digital
from gnuradio import eng_notation
from gnuradio import gr
#-----------------------#
import struct
from gnuradio import atsc
#-----------------------#
from gnuradio.eng_option import eng_option
from gnuradio.gr import firdes
from gnuradio.qtgui import qtgui
from grc_gnuradio import blks2 as grc_blks2
from optparse import OptionParser
import PyQt4.Qwt5 as Qwt
#-----------#
import random
#-----------#
import sip
import sys

class QAM16(gr.top_block, Qt.QWidget):

	def __init__(self):
		gr.top_block.__init__(self, "QAM16")
		Qt.QWidget.__init__(self)
		self.setWindowTitle("QAM16")
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
		#------------------------------------------------#
		self.Packets_Number = 8096*128
		##################################################

		

		#--------------------------------------------------------------------------------------------------------------#
		#with open('/home/katsikas/katsikas-repo/Gnuradio/Common/Text.txt', 'rb') as f:
		with open('/home/katsikas/katsikas-repo/Simulink/Korgialas_GeiaSou.ts', 'rb') as f:
			self.ts = self.make_fake_transport_stream_packet(self.Packets_Number,f) 
		#--------------------------------------------------------------------------------------------------------------#		
	
	

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
			True, #plotfreq
			False, #plotwaterfall
			True, #plottime
			False, #plotconst
		)
		self._qtgui_sink_x_0_win = sip.wrapinstance(self.qtgui_sink_x_0.pyqwidget(), Qt.QWidget)
		self.top_layout.addWidget(self._qtgui_sink_x_0_win)
		self.gr_throttle_0 = gr.throttle(gr.sizeof_gr_complex*1, samp_rate)
		self.gr_vector_source_0 = gr.vector_source_b(self.ts, True, 1)
		self.gr_file_sink_0 = gr.file_sink(gr.sizeof_char*1, "/home/katsikas/katsikas-repo/Gnuradio/Common/Results.ts")
		self.gr_file_sink_0.set_unbuffered(False)
		self.digital_ofdm_mod_0 = grc_blks2.packet_mod_b(digital.DVBT_ofdm_mod(
				options=grc_blks2.options(
					modulation="qam64",
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
					modulation="qam64",
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

		##################################################
		# Connections
		##################################################
		self.connect((self.gr_throttle_0, 0), (self.qtgui_sink_x_0, 0))
		self.connect((self.digital_ofdm_mod_0, 0), (self.gr_throttle_0, 0))
		self.connect((self.digital_ofdm_mod_0, 0), (self.digital_ofdm_demod_0, 0))
		#self.connect((self.gr_file_source_0, 0), (self.digital_ofdm_mod_0, 0))
		self.connect((self.gr_vector_source_0, 0), (self.digital_ofdm_mod_0, 0))
		self.connect((self.digital_ofdm_demod_0, 0), (self.gr_file_sink_0, 0))

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
		self.qtgui_sink_x_0.set_frequency_range(self.Transmission_Frequency, 8e6)

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

	##################################################################
	def make_transport_stream_packet(self):
		"""
		Create and return an MPEG transport stream according to the DVB-T standard.
		A ts packet should of 188 bytes length.The first byte is called synchronization 
		byte and its value is by default 47(HEX) or 71(dec) or 01 000 111(binary).
		The processing order at the transmitting side shall always start from the MSB.
		All bytes except the first sync byte are scrambled with a PRBS sequence. The 
		PRBS sequence shall be initiated at the start of every eight transport packets.
		To provide an initialization signal for the descrambler, the MPEG-2 sync byte of
		the first transport packet in a group of eight packets is bit-wise inverted from 
		47(HEX) to B8(HEX).

		@Return an MPEG TS scrambled stream according to the DVB-T standard.
		The whole process is known as 
		Transport multiplex adaptation and randomization for energy dispersal.
		"""
			
		PRBS_PERIOD = 8
		MPEG_SYNC_BYTE = 0x47
		MPEG_INVERTED_SYNC_BYTE = 0xB8
		INIT_PRBS_REGISTERS = [1,0,0,1,0,1,0,1,0,0,0,0,0,0,0] 

		
		
	########################################################################################


	########################################################################################
	# My Functions
	def make_fake_transport_stream_packet(self,npkts,f):
    		"""
    		Return a sequence of 8-bit ints that represents an MPEG Transport Stream packet.

    		@param npkts: how many 188-byte packets to return

    		FYI, each ATSC Data Frame contains two Data Fields, each of which contains
    		312 data segments.  Each transport stream packet maps to a data segment.
    		"""

    		r = [0] * (npkts * 188)
    		i = 0

		MPEG_SYNC_BYTE = 0x47
		MPEG_INVERTED_SYNC_BYTE = 0xB8

    		for j in range(npkts):
			if i == 0:
				r[i+0] = MPEG_INVERTED_SYNC_BYTE
			else:
        			r[i+0] = MPEG_SYNC_BYTE
        		r[i+1] = random.randint(0, 0) # top bit (transport error bit) clear
			r[i+2] = random.randint(0, 0)
			r[i+3] = random.randint(0, 0)
        		i = i + 4
			
       			for n in range(184):
    				byte = f.read(1)
				if byte != "":
					value = struct.unpack('B',byte)[0]
            				r[i + n] = value
				else:
					r[i + n] = 0
        		i = i + 184
			
    		return r
	########################################################################################


if __name__ == '__main__':
	parser = OptionParser(option_class=eng_option, usage="%prog: [options]")
	(options, args) = parser.parse_args()
	qapp = Qt.QApplication(sys.argv)
	tb = QAM16()
	tb.start()
	tb.show()
	qapp.exec_()
	tb.stop()

