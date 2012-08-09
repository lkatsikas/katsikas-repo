#!/usr/bin/env python
##################################################
# Gnuradio Python Flow Graph
# Title: Top Block
# Generated: Thu Aug  9 11:50:24 2012
################################################## 

import random

from gnuradio import gr, digital

def get_BER(constellation, noise_level, data_length=1000):
    data = tuple(
        [random.randint(0,1) for i in range(0, data_length)])
    tb = gr.top_block()
    src = gr.vector_source_b(data)
    pack = gr.unpacked_to_packed_bb(1, gr.GR_MSB_FIRST)
    bytes2chunks = gr.packed_to_unpacked_bb(constellation.bits_per_symbol(),
                                            gr.GR_MSB_FIRST)

    print constellation.points()
    #print constellation.bits_per_symbol()
    #print constellation.pre_diff_code()

    chunks2symbols = gr.chunks_to_symbols_bc(constellation.points())    
    decoder = digital.constellation_decoder_cb(constellation)
    unpack = gr.unpack_k_bits_bb(constellation.bits_per_symbol())
    snk = gr.vector_sink_b()
    tb.connect(src, pack, bytes2chunks, chunks2symbols)
    tb.connect(chunks2symbols, decoder, unpack, snk)
    tb.run()
    errors = 0
    for i, j in zip(data, snk.data()):
        if i != j:
            errors += 1
    return 1.0*errors/data_length

if __name__ == "__main__":
    points = [1+1j, 1-1j, -1+1j, -1-1j]
    constellation = digital.constellation_dvbt_qpsk().base()
    #constellation = digital.constellation_calcdist(points, [], 1, 1).base()
    BER = get_BER(constellation, 1)
    print("BER = {0}".format(BER))
