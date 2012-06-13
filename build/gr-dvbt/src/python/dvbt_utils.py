#
# Copyright 2006 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
#

import random
import sys


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
			"""
			if i == 0:
				r[i+0] = MPEG_INVERTED_SYNC_BYTE
			else:
        			r[i+0] = MPEG_SYNC_BYTE
        		r[i+1] = random.randint(0, 0) # top bit (transport error bit) clear
			r[i+2] = random.randint(0, 0)
			r[i+3] = random.randint(0, 0)
        		i = i + 4
			"""
       			for n in range(188):
    				byte = f.read(1)
				if byte != "":
					value = struct.unpack('B',byte)[0]
            				r[i + n] = value
				else:
					r[i + n] = 0
        		i = i + 188
			
    		return r



	def pad_stream(self,src, sizeof_total, sizeof_pad):
    		sizeof_valid = sizeof_total - sizeof_pad
    		assert sizeof_valid > 0
    		assert (len(src) % sizeof_valid) == 0
    		npkts = len(src) // sizeof_valid
    		dst = [0] * (npkts * sizeof_total)
    		for i in range(npkts):
        		src_s = i * sizeof_valid
        		dst_s = i * sizeof_total
        		dst[dst_s:dst_s + sizeof_valid] = src[src_s:src_s + sizeof_valid]
    		return dst


	def depad_stream(self,src, sizeof_total, sizeof_pad):
    		sizeof_valid = sizeof_total - sizeof_pad
    		assert sizeof_valid > 0
    		assert (len(src) % sizeof_total) == 0
    		npkts = len(src) // sizeof_total
    		dst = [0] * (npkts * sizeof_valid)
    		for i in range(npkts):
        		src_s = i * sizeof_total
        		dst_s = i * sizeof_valid
        		dst[dst_s:dst_s + sizeof_valid] = src[src_s:src_s + sizeof_valid]
    		return dst

	########################################################################################

