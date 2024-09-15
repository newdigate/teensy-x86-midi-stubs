cmake_minimum_required(VERSION 3.5)
project(teensy_x86_midi_stubs_rtmidi)

set(CMAKE_CXX_STANDARD 14)

set(teensy_x86_midi_stubs_rtmidi_VERSION 1.0.0)

#find_path(RTMIDI_INCLUDE_DIR RtMidi.h
#  PATHS
#    /usr/local/include
#    /usr/include
#    /usr/include/rtmidi)
#include_directories(${RTMIDI_INCLUDE_DIR})

set(HEADER_FILES RtMidiMIDI.h RtMidiTransport.h)

add_library(teensy_x86_midi_stubs_rtmidi INTERFACE)
