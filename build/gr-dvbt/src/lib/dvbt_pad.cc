/* -*- c++ -*- */
/*
 * Copyright 2006,2010 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <dvbt_pad.h>
#include <dvbt_types.h>
#include <gr_io_signature.h>


dvbt_pad_sptr
dvbt_make_pad()
{
  return gnuradio::get_initial_sptr(new dvbt_pad());
}

dvbt_pad::dvbt_pad()
  : gr_sync_decimator("dvbt_pad",
		  gr_make_io_signature(1, 1, sizeof(unsigned char)),
		  gr_make_io_signature(1, 1, sizeof(dvbt_mpeg_packet)),
		  DVBT_MPEG_PACKET_LENGTH)
{
  reset();
}

void
dvbt_pad::forecast (int noutput_items, gr_vector_int &ninput_items_required)
{
	unsigned ninputs = ninput_items_required.size();
  	for (unsigned i = 0; i < ninputs; i++){
    		ninput_items_required[i] = noutput_items * DVBT_MPEG_PACKET_LENGTH;
	}
}


int
dvbt_pad::work (int noutput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items)
{
	int i = 0;
	const unsigned char *in = (const unsigned char *) input_items[0];
  	dvbt_mpeg_packet *out = (dvbt_mpeg_packet *) output_items[0];


  	for (i = 0; i < noutput_items; i++){
    		for (int j = 0; j < ATSC_MPEG_PACKET_LENGTH; j++){
        		out[i].data[j] = in[i * ATSC_MPEG_PACKET_LENGTH + j];
		}
	}

	return noutput_items;
}




