//
// Created by Paul Cimarusti on 7/16/25.
//

#include <iostream>
#include "SynthController.h"
#include "../Audio/VoiceManager.h"

SynthController::SynthController(VoiceManager *pVoiceManager_) : pVoiceManager(pVoiceManager_) {}

void SynthController::onMidiMessage(Constants::MidiMessage midiMessage)
{
    // If the message is of note on or note off type
    if (midiMessage.type == Constants::MessageType::NoteOn)
        pVoiceManager->noteOn(midiMessage.data1, midiMessage.data2);
    else if (midiMessage.type == Constants::MessageType::NoteOff)
        pVoiceManager->noteOff(midiMessage.data1);
    else
        std::cerr << "\nSYNTH CONTROLLER: MIDI MESSAGE OF UN-IMPLEMENTED TYPE SENT\n";
}