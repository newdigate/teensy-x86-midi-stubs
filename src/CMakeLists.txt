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
