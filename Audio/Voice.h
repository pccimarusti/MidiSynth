//
// Created by Paul Cimarusti on 7/18/25.
//

#ifndef MIDISYNTH_VOICE_H
#define MIDISYNTH_VOICE_H


#include "Oscillator.h"
#include "../Constants.h"

struct ADSR {
    enum class ADSRState {
        Idle, Attack, Release
    };
    ADSR(float attackTime_, float releaseTime_);

    ADSRState adsrState = ADSRState::Idle;
    float envelope = 0.0f;
    float attackTime;
    float releaseTime;
    float attackIncrement;
    float releaseIncrement;
};

// @brief each voice object has an oscillator, and manages ADSR
class Voice
{
public:
    Voice();
    void noteOn(int note, int velocity);
    void noteOff(int note);
    void generateBlock(float* buff, unsigned int nFrames);
    bool isActive() const;

    int currentMidiNote = -1;
private:
    Oscillator osc;
    ADSR adsr;
    bool active = false;

};


#endif //MIDISYNTH_VOICE_H
