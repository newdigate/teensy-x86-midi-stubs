cmake_minimum_required(VERSION 3.5)
project(teensy_x86_midi_stubs_rtmidi)

set(CMAKE_CXX_STANDARD 14)

set(teensy_x86_midi_stubs_rtmidi_VERSION 1.0.0)

find_path(RTMIDI_INCLUDE_DIR NAMES RtMidi/RtMidi.h)
include_directories(${RTMIDI_INCLUDE_DIR}/RtMidi)

set(HEADER_FILES RtMidiMIDI.h RtMidiTransport.h)

add_library(teensy_x86_midi_stubs_rtmidi INTERFACE ${HEADER_FILES})

set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include/teensy_x86_midi_stubs_rtmidi/)
set(LIB_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib/teensy_x86_midi_stubs_rtmidi )

set_target_properties(teensy_x86_midi_stubs_rtmidi PROPERTIES PUBLIC_HEADER "${HEADER_FILES}")

include(CMakePackageConfigHelpers)
configure_package_config_file(../../../cmake/teensy_x86_midi_stubs_rtmidi.cmake.in
		${CMAKE_CURRENT_BINARY_DIR}/teensy_x86_midi_stubs_rtmidiConfig.cmake
		INSTALL_DESTINATION ${LIB_INSTALL_DIR}/teensy_x86_midi_stubs_rtmidi/cmake
		PATH_VARS)

write_basic_package_version_file(
		${CMAKE_CURRENT_BINARY_DIR}/teensy_x86_midi_stubs_rtmidiConfigVersion.cmake
		VERSION ${teensy_x86_midi_stubs_rtmidi_VERSION}
		COMPATIBILITY SameMajorVersion )

install(TARGETS teensy_x86_midi_stubs_rtmidi DESTINATION
		LIBRARY DESTINATION ${LIB_INSTALL_DIR}
		# ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
		PUBLIC_HEADER DESTINATION "include/teensy_x86_midi_stubs_rtmidi"
		)

install(FILES
		${CMAKE_CURRENT_BINARY_DIR}/teensy_x86_midi_stubs_rtmidiConfig.cmake
		${CMAKE_CURRENT_BINARY_DIR}/teensy_x86_midi_stubs_rtmidiConfigVersion.cmake
		DESTINATION "lib/cmake/teensy_x86_midi_stubs_rtmidi" )