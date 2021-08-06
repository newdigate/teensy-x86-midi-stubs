project(teensy_x86_midi_stubs)

set(CMAKE_CXX_STANDARD 14)

set(teensy_x86_midi_stubs_VERSION 1.0.0)

set(HEADER_FILES
    midi_Namespace.h
    midi_Defs.h
    midi_Message.h
    midi_Platform.h
    midi_Settings.h
    MIDI.cpp
    MIDI.hpp
    MIDI.h
    serialMIDI.h
)

add_library(teensy_x86_midi_stubs STATIC ${HEADER_FILES})

set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include/teensy_x86_midi_stubs/)
set(LIB_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib/teensy_x86_midi_stubs )

set_target_properties(teensy_x86_midi_stubs PROPERTIES PUBLIC_HEADER "${HEADER_FILES}")

include(CMakePackageConfigHelpers)
configure_package_config_file(../cmake/teensy_x86_midi_stubs.cmake.in
		${CMAKE_CURRENT_BINARY_DIR}/teensy_x86_midi_stubsConfig.cmake
		INSTALL_DESTINATION ${LIB_INSTALL_DIR}/teensy_x86_midi_stubs/cmake
		PATH_VARS)

write_basic_package_version_file(
		${CMAKE_CURRENT_BINARY_DIR}/teensy_x86_midi_stubsConfigVersion.cmake
		VERSION ${teensy_x86_midi_stubs_VERSION}
		COMPATIBILITY SameMajorVersion )

install(TARGETS teensy_x86_midi_stubs DESTINATION
		LIBRARY DESTINATION ${LIB_INSTALL_DIR}
		ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
		PUBLIC_HEADER DESTINATION "include/teensy_x86_midi_stubs"
		)

install(FILES
		${CMAKE_CURRENT_BINARY_DIR}/teensy_x86_midi_stubsConfig.cmake
		${CMAKE_CURRENT_BINARY_DIR}/teensy_x86_midi_stubsConfigVersion.cmake
		${CMAKE_CURRENT_SOURCE_DIR}/../cmake/uninstall.cmake
		DESTINATION "lib/cmake/teensy_x86_midi_stubs" )

##
# copied from: https://gist.github.com/royvandam/3033428
# Add uninstall target
# Requirements: Copy the uninstall.cmake file to the appropriate CMAKE_MODULE_PATH.
add_custom_target(uninstall
		"${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_SOURCE_DIR}/../cmake/uninstall.cmake")