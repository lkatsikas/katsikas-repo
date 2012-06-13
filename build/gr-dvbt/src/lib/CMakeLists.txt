# Copyright 2011-212 Free Software Foundation, Inc.
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

########################################################################
# Setup the include and linker paths
########################################################################
include_directories(
    ${GNURADIO_CORE_INCLUDE_DIRS}
    ${GR_DVBT_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR}
)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})


########################################################################
# Setup library
########################################################################
list(APPEND gr_dvbt_sources
    dvbt_pad.cc
    # ----> put .cc files
)

list(APPEND dvbt_libs
    gnuradio-core
    ${Boost_LIBRARIES}
)

add_library(gnuradio-dvbt SHARED ${gr_dvbt_sources})
target_link_libraries(gnuradio-dvbt ${dvbt_libs})
GR_LIBRARY_FOO(gnuradio-dvbt RUNTIME_COMPONENT "dvbt_runtime" DEVEL_COMPONENT "dvbt_devel")

########################################################################
# Build and register unit test
########################################################################
if(ENABLE_TESTING)

include_directories(${CPPUNIT_INCLUDE_DIRS})
link_directories(${CPPUNIT_LIBRARY_DIRS})

list(APPEND test_dvbti_sources
    qa_dvbti.cc
    # ---> qa_atsci_basic_trellis_encoder.cc
)

include(GrTest)
set(GR_TEST_TARGET_DEPS gnuradio-dvbt gnuradio-core gruel volk)
add_executable(test_dvbt ${test_dvbt_sources} test_dvbt.cc)
target_link_libraries(test_dvbt gnuradio-dvbt gnuradio-core ${CPPUNIT_LIBRARIES})
GR_ADD_TEST(dvbt-test test_dvbt)

endif(ENABLE_TESTING)

########################################################################
# Install public header files
########################################################################
install(FILES
    dvbt_api.h
    dvbt_pad.h
    dvbt_types.h
    dvbt_consts.h
	# ----> put .h files.  e.g: atsc_derandomizer.h
    DESTINATION ${GR_INCLUDE_DIR}/gnuradio
    COMPONENT "dvbt_devel"
)

########################################################################
# Setup swig generation
########################################################################
if(ENABLE_PYTHON)
include(GrPython)
include(GrSwig)

set(GR_SWIG_INCLUDE_DIRS
    ${GR_DVBT_INCLUDE_DIRS}
    ${GNURADIO_CORE_SWIG_INCLUDE_DIRS}
)

# add Doxygen docs to python
set(GR_SWIG_DOC_FILE ${CMAKE_CURRENT_BINARY_DIR}/dvbt_swig_doc.i)
set(GR_SWIG_DOC_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

set(GR_SWIG_LIBRARIES gnuradio-dvbt)

GR_SWIG_MAKE(dvbt dvbt.i)

GR_SWIG_INSTALL(
    TARGETS dvbt
    DESTINATION ${GR_PYTHON_DIR}/gnuradio
    COMPONENT "dvbt_python"
)

install(
    FILES dvbt.i
    ${CMAKE_CURRENT_BINARY_DIR}/dvbt_swig_doc.i
    DESTINATION ${GR_INCLUDE_DIR}/gnuradio/swig
    COMPONENT "dvbt_swig"
)

endif(ENABLE_PYTHON)
