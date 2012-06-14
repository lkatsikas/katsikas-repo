from gnuradio import gr
from dvbt_utils import *

import sys
import random


class dvbt_source(gr.hier_block2):
    """
    MPEG Transport stream source for DVBT.
    """
    def __init__(self):

        """
        Pad tranport stream packets to 256 bytes and reformat appropriately.

        @param ts: MPEG transport stream.
        @type  ts: sequence of ints in [0,255]; len(ts) % 188 == 0
        """
	Packets_Number = 8096

	with open('/home/katsikas/katsikas-repo/Simulink/Korgialas_GeiaSou.ts', 'rb') as f:
                        ts = make_fake_transport_stream_packet(Packets_Number,f)

        src = gr.vector_source_b(pad_transport_stream(ts))
        s2v = gr.stream_to_vector(gr.sizeof_char, atsc.sizeof_atsc_mpeg_packet)

        gr.hier_block2.__init__(self, "dvbt_source",
                                gr.io_signature(0, 0, 0),
                                s2v.output_signature())
        self.connect(src, s2v, self)

