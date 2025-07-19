//
// Created by Paul Cimarusti on 7/18/25.
//

#ifndef MIDISYNTH_VOICEMANAGER_H
#define MIDISYNTH_VOICEMANAGER_H


#include "Voice.h"
#include <vector>
#include "../Interfaces/ISoundSource.h"

// @brief manages a list of voice objects, sound source for audio engine
class VoiceManager : public ISoundSource
{
public:
//    VoiceManager();
    void noteOn(int note, int velocity) override;
    void noteOff(int note) override ;
    void generateBlock(float* buff, unsigned int nFrames) override;

private:
    Voice voices[8];

    // Temp
//    float phase = 0.0f;
};


#endif //MIDISYNTH_VOICEMANAGER_H
