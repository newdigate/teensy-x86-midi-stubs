cmake_minimum_required(VERSION 3.5)
project(teensy_x86_midi_stubs_rtmidi)
find_path(RTMIDI_INCLUDE_DIR NAMES RtMidi.h)
include_directories(${RTMIDI_INCLUDE_DIR})

add_library(teensy_x86_midi_stubs_rtmidi INTERFACE RtMidiMIDI.h)
