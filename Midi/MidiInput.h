//
// Created by Paul Cimarusti on 7/15/25.
//

#ifndef MIDISYNTH_MIDIINPUT_H
#define MIDISYNTH_MIDIINPUT_H


#include <RtMidi.h>

// Synth Controller to pass MIDI data to
class SynthController;

// @brief handles midi input and passes data to SynthController
class MidiInput
{
public:
    explicit MidiInput(SynthController* pSynthController_);
    // @brief displays available midi ports, takes user input, and opens that port
    void connectUserInputMidiPort();

private:
    RtMidiIn midiIn;
    SynthController* pSynthController;
    static void midiCallBack(double timeStamp, std::vector<unsigned char>* message, void* userData);
};


#endif //MIDISYNTH_MIDIINPUT_H
