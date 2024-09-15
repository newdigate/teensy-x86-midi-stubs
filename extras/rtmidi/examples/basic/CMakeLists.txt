cmake_minimum_required(VERSION 3.5)
project(basic_rtmidi_example)

set(CMAKE_CXX_STANDARD 14)

find_package(teensy_x86_stubs)
include_directories(${teensy_x86_stubs_INCLUDE_DIR})

find_package(teensy_x86_midi_stubs)
include_directories(${teensy_x86_midi_stubs_INCLUDE_DIR})

add_executable(basic basic.cpp)
target_link_libraries(basic -L/usr/local/lib/ rtmidi)
target_link_libraries(basic ${teensy_x86_stubs_LIBS})
target_link_libraries(basic ${teensy_x86_midi_stubs_LIBS})
target_link_libraries(basic teensy_x86_midi_stubs_rtmidi)
