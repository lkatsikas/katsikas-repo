/* -*- c++ -*- */
/*
 * Copyright 2001,2006 Free Software Foundation, Inc.
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

#ifndef _DVBT_TYPES_H_
#define _DVBT_TYPES_H_

#include <cstring>
#include <cassert>
#include <dvbt_consts.h>


class dvbt_mpeg_packet {
 public:
  static const int PAD  = 68;
  unsigned char data[DVBT_MPEG_DATA_LENGTH + 1];        // first byte is sync
  unsigned char _pad_[PAD];                            // pad to power of 2

  // overload equality operator
  bool operator== (const dvbt_mpeg_packet &other) const {
    return std::memcmp (data, other.data, sizeof (data)) == 0;
  };

  bool operator!= (const dvbt_mpeg_packet &other) const {
    return !(std::memcmp (data, other.data, sizeof (data)) == 0);
  };
};

#endif /* _DVBT_TYPES_H_ */
