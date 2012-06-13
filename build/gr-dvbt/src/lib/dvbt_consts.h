/* -*- c++ -*- */
/*
* Copyright 2002 Free Software Foundation, Inc.
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
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with GNU Radio; see the file COPYING. If not, write to
* the Free Software Foundation, Inc., 51 Franklin Street,
* Boston, MA 02110-1301, USA.
*/

#ifndef _DVBT_CONSTS_H_
#define _DVBT_CONSTS_H_

static const int DVBT_MPEG_DATA_LENGTH = 184; // Data
static const int DVBT_MPEG_PACKET_LENGTH = 188;	// TS Header + Data
static const int DVBT_MPEG_RS_ENCODED_LENGTH = 204; // Packet after RS Encoding
static const int DVBT_SUPER_FRAME_LENGTH = 1504; // Superframe consists of 8 packets

static const int PRBS_PERIOD = 8;
static const int MPEG_SYNC_BYTE = 0x47;
static const int MPEG_INVERTED_SYNC_BYTE = 0xB8;
//static const int INIT_PRBS_REGISTERS[] = [1,0,0,1,0,1,0,1,0,0,0,0,0,0,0];

#endif // _DVBT_CONSTS_H_




