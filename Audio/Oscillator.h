//
// Created by Paul Cimarusti on 7/14/25.
//

#ifndef MIDISYNTH_OSCILLATOR_H
#define MIDISYNTH_OSCILLATOR_H


#include <atomic>
#include "../Constants.h"

// @brief manages single note
class Oscillator
{
public:
    enum class WaveType {
        Sine, Square
    };

    void setFrequency(float frequency_);
//    [[nodiscard]] float getFrequency() const;
    void setWaveType(WaveType waveType_);

    float noteOn(int note, int velocity);
    float noteOff(int note);
    void generateBlock(float* buff, unsigned int nFrames);
    void onReceiveMidiNote(Constants::MidiMessage midiMessage);

private:
    WaveType waveType = WaveType::Sine;
    std::atomic<float> frequency = 261.63f;
    bool isPlaying = false;
    float phase = 0.0f;
};


#endif //MIDISYNTH_OSCILLATOR_H
