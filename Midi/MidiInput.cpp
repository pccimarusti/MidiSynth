//
// Created by Paul Cimarusti on 7/15/25.
//

#include "MidiInput.h"
#include "../SynthController/SynthController.h"

MidiInput::MidiInput(SynthController* pSynthController_) : pSynthController(pSynthController_) {}

void MidiInput::connectUserInputMidiPort()
{
    unsigned int midiPortCount = midiIn.getPortCount();
    unsigned int selectedMidiPortNumber;

    // Display ports
    std::cout << "\n--MIDI INPUT--\nSelect a midi port...\n";
    for (int i = 0; i < midiPortCount; i++ )
        std::cout << "\t" << "[" << i << "] " << midiIn.getPortName(i) << '\n';

    while (true)
    {
        // User select port
        std::cout << "Port number: ";
        std::cin >> selectedMidiPortNumber;
//        selectedMidiPortNumber = 2;

        // Open selected port
        if (selectedMidiPortNumber < midiPortCount && !std::cin.fail())
        {
            std::cout << "Selected port " << selectedMidiPortNumber << "\n";
            midiIn.openPort(selectedMidiPortNumber);
            midiIn.setCallback(&MidiInput::midiCallBack, this);
            break;
        } else
        {
            std::cout << "Invalid midi port...\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
    }
}


// Called every time a midi message is received
void MidiInput::midiCallBack(double timeStamp, std::vector<unsigned char> *message , void* userData)
{
    if (!message || message->empty())
    {
        std::cerr << "MIDI INPUT: VOID MIDI CALLBACK";
        return;
    }

    Constants::MidiMessage midiMessage;

    // Parse Message
    unsigned char status = (*message)[0];
    unsigned char data1 = (*message)[1];
    unsigned char data2 = (*message)[2];

    // Interpret message type
    unsigned char messageTypeBits = status & 0xF0;
    switch (messageTypeBits)
    {
        case 0x90: midiMessage.type = Constants::MessageType::NoteOn;
            break;
        case 0x80: midiMessage.type = Constants::MessageType::NoteOff;
            break;
        case 0xA0: midiMessage.type = Constants::MessageType::PolyphonicAftertouch;
            break;
        case 0xB0: midiMessage.type = Constants::MessageType::ControlChange;
            break;
        case 0xC0: midiMessage.type = Constants::MessageType::ProgramChange;
            break;
        case 0xD0: midiMessage.type = Constants::MessageType::ChannelAftertouch;
            break;
        case 0xE0: midiMessage.type = Constants::MessageType::PitchWheel;
            break;
        default: midiMessage.type = Constants::MessageType::Unknown;
            break;
    }

    // Interpret channel number
    midiMessage.channelNum = static_cast<int>(status & 0x0f) + 1;

    // Interpret data 1
    midiMessage.data1 = static_cast<int>(data1);

    // Interpret data 2
    midiMessage.data2 = static_cast<int>(data2);

    // Print MIDI Message
    std::cout << "\n--MIDI INPUT--\n";
    std::cout << "[Message]\n";
    std::cout << "Time: " << timeStamp << "\n";

    if (midiMessage.type == Constants::MessageType::NoteOn)
        std::cout << "Note On\n";
    else if (midiMessage.type == Constants::MessageType::NoteOff)
        std::cout << "Note Off\n";
    else
        std::cout << "Other\n";

    std::cout << "Channel Num: " << midiMessage.channelNum << '\n';
    std::cout << "Data 1: " << midiMessage.data1 << '\n';
    std::cout << "Data 2: " << midiMessage.data2 << '\n';

    auto* pMidiInput = static_cast<MidiInput*>(userData);
    if (pMidiInput)
        pMidiInput->pSynthController->onMidiMessage(midiMessage);
}
