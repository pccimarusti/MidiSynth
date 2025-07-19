cmake_minimum_required(VERSION 3.28)
project(MidiSynth)

set(CMAKE_CXX_STANDARD 17)

# Disable library extra's to prevent naming conflicts
set(BUILD_TESTING OFF CACHE BOOL "Disable test targets")
set(RTAUDIO_BUILD_EXAMPLES OFF CACHE BOOL "Disable RtAudio examples")
set(RTAUDIO_BUILD_TESTING OFF CACHE BOOL "Disable RtAudio testing")
set(RTMIDI_BUILD_TESTING OFF CACHE BOOL "Disable RtAudio testing")
set(RTMIDI_BUILD_SHARED_LIBS OFF CACHE BOOL "Use static RtMidi")

add_subdirectory(rtaudio)
add_subdirectory(rtmidi)

add_executable(MidiSynth
        main.cpp

        Audio/AudioEngine.cpp
        Audio/AudioEngine.h
        Audio/Oscillator.cpp
        Audio/Oscillator.h

        Midi/MidiInput.cpp
        Midi/MidiInput.h

        Constants.h
        SynthController/SynthController.cpp
        SynthController/SynthController.h
        Interfaces/ISoundSource.h
        Audio/Voice.cpp
        Audio/Voice.h
        Audio/VoiceManager.cpp
        Audio/VoiceManager.h
)

# Adds subdirectories, and machine frameworks to handle them
target_link_libraries(MidiSynth
        PRIVATE
        rtaudio
        rtmidi
        "-framework CoreAudio"
        "-framework AudioToolbox"
        "-framework CoreFoundation"
        "-framework CoreMIDI")
