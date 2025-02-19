cmake_minimum_required(VERSION 3.5)
project(basic_rtmidi_example)

set(CMAKE_CXX_STANDARD 14)
include_directories(../../../../src)
include_directories(../../src)

add_executable(basic basic.cpp)
target_link_libraries(basic rtmidi)
target_link_libraries(basic teensy_x86_stubs)
target_link_libraries(basic teensy_x86_midi_stubs)
target_link_libraries(basic teensy_x86_midi_stubs_rtmidi)
