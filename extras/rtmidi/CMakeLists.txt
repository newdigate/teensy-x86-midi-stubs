cmake_minimum_required(VERSION 3.5)

include(../../cmake_declare_and_fetch.cmake.in)
DeclareAndFetch(rtmidi                      https://github.com/thestk/rtmidi.git master "/")

add_subdirectory(src)
add_subdirectory(examples/basic)