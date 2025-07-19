//
// Created by Paul Cimarusti on 7/15/25.
//

#ifndef MIDISYNTH_CONSTANTS_H
#define MIDISYNTH_CONSTANTS_H


#include <cmath>

namespace Constants {
    // -- Math constants --
    constexpr float TWOPI = 2 * M_PI;
//    constexpr float PI = M_PI;

    // -- MIDI --
    enum class MessageType {
        NoteOn, NoteOff, PolyphonicAftertouch, ControlChange, ProgramChange, ChannelAftertouch, PitchWheel, Unknown
    };

    struct MidiMessage {
        MessageType type = MessageType::Unknown;
        int channelNum = 1;
        int data1 = 60; // Note Number, Controller Number, Program Number, Pressure, LSB
        int data2 = 0; // Velocity, Pressure, Data, MSB
    };

    // inline allows multiple function calls from different files
    inline float midiNumToFrequency(int num) {
        return static_cast<float>(440 * pow(2,((num-69)/12.0)));
    }

    // -- Audio --
    inline const int sampleRate = 44100;
}

#endif //MIDISYNTH_CONSTANTS_H
