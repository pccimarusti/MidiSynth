//
// Created by Paul Cimarusti on 7/18/25.
//

#include "Voice.h"
#include <iostream>

// Init ADSR
ADSR::ADSR(float attackTime_, float releaseTime_) : attackTime(attackTime_), releaseTime(releaseTime_) {
    attackIncrement = 1.0f / (attackTime_ * Constants::sampleRate);
    releaseIncrement = 1.0f / (releaseTime_ * Constants::sampleRate);
}

Voice::Voice() : adsr(0.5f, 0.3f) {}

bool Voice::isActive() const { return active; }

void Voice::noteOn(int note, int velocity)
{
    osc.noteOn(note, velocity);
    currentMidiNote = note;
    adsr.adsrState = ADSR::ADSRState::Attack;

    active = true; // Note is beginning
}

void Voice::noteOff(int note)
{
    osc.noteOff(note);
    currentMidiNote = -1;
    adsr.adsrState = ADSR::ADSRState::Release;
}

void Voice::generateBlock(float *buff, unsigned int nFrames)
{
    if(nFrames != 256) {
        std::cerr << "nFrames != 256\n";
    }
    float tempBuffer[256];
    osc.generateBlock(tempBuffer, nFrames);

    for (unsigned int frame = 0; frame < nFrames; frame++)
    {
        // ADSR
        switch(adsr.adsrState)
        {
            case ADSR::ADSRState::Attack:
                adsr.envelope += adsr.attackIncrement;
                if (adsr.envelope >= 1.0f)
                {
                    adsr.envelope = 1.0f;
                    adsr.adsrState = ADSR::ADSRState::Idle;
                }
                break;
            case ADSR::ADSRState::Release:
                adsr.envelope -= adsr.releaseIncrement;

                if (adsr.envelope <= 0.0f)
                {
                    adsr.envelope = 0.0f;
                    adsr.adsrState = ADSR::ADSRState::Idle;

                    active = false;                 // Note is finished
                }
                break;
            default:
//                adsr.envelope = 1.0f;
                break;
        }

        buff[frame] = tempBuffer[frame] * adsr.envelope;
    }
}


