//
// Created by Paul Cimarusti on 7/16/25.
//

#ifndef MIDISYNTH_SYNTHCONTROLLER_H
#define MIDISYNTH_SYNTHCONTROLLER_H


#include "../Midi/MidiInput.h"
#include "../Constants.h"

// Oscillator to pass MIDI data to
class VoiceManager;

// @brief receives inputted midi data from MidiInput, and forwards it to Oscillator
class SynthController
{
public:
    explicit SynthController(VoiceManager *pVoiceManager_);
    // @brief called by midi input everytime a midi message is received
    void onMidiMessage(Constants::MidiMessage midiMessage);

private:
    VoiceManager* pVoiceManager;
};


#endif //MIDISYNTH_SYNTHCONTROLLER_H
