//
// Created by Paul Cimarusti on 7/14/25.
//

#include "Oscillator.h"
#include <iostream>
#include <cmath>

void Oscillator::setFrequency(float frequency_) { frequency.store(frequency_); }

//float Oscillator::getFrequency() const { return frequency.load(); }

void Oscillator::setWaveType(Oscillator::WaveType waveType_) { waveType = waveType_; }

float Oscillator::noteOn(int note, int velocity)
{
    phase = 0.0f;
//    isPlaying = true;
    setFrequency(Constants::midiNumToFrequency(note));
    return 0;
}

float Oscillator::noteOff(int note)
{
    return 0;
}

void Oscillator::generateBlock(float* buff, unsigned int nFrames)
{
    float freq = frequency.load();
    for (int frame = 0; frame < nFrames; frame++)
    {
        phase += float(Constants::TWOPI * freq / Constants::sampleRate);

        // Wraps phase from 0 to 2Pi
        if (phase >= Constants::TWOPI)
            phase -= Constants::TWOPI;

        // Calculates sample
        float sample = sinf(phase) * 0.3f;

        buff[frame] = sample;
    }
}

// This code should never run, as noteOn and noteOff are managed by voices
void Oscillator::onReceiveMidiNote(Constants::MidiMessage midiMessage)
{
    Constants::MessageType messageType = midiMessage.type;

    switch (messageType)
    {
        case Constants::MessageType::NoteOn:
            noteOn(midiMessage.data1, midiMessage.data2);
            std::cout << "Note on\n";
            break;
        case Constants::MessageType::NoteOff:
            noteOff(midiMessage.data1);
            break;
        default:
            std::cerr << "OSCILLATOR: NON-IMPLEMENTED MIDI MESSAGE TYPE RECEIVED\n";
            break;
    }

    std::cout << "\n--OSCILLATOR--\nRECEIVED MIDI INFORMATION";
}


