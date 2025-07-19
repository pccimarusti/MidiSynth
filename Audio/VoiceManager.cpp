//
// Created by Paul Cimarusti on 7/18/25.
//

#include "VoiceManager.h"
#include <iostream>

//VoiceManager::VoiceManager()
//{
//
//}

void VoiceManager::noteOn(int note, int velocity)
{
    // Search for inactive voice and assign it the specified note
    for (Voice& voice : voices)
    {
        if (!voice.isActive())
        {
            std::cerr << "\nVoice made active\n";
            voice.noteOn(note, velocity);
            return;
        }
    }
}

void VoiceManager::noteOff(int note)
{
    // Search for voice with specified note and deactivate it
    for (Voice& voice : voices )
    {
        if (voice.currentMidiNote == note && voice.isActive())
        {
            std::cerr << "\nVoice made inactive\n";
            voice.noteOff(note);
            return;
        }
    }
}

void VoiceManager::generateBlock(float *buff, unsigned int nFrames)
{
    // Clear main buffer
    for (unsigned int i = 0; i < nFrames; i++)
        buff[i] = 0;

    for (Voice& voice : voices)
    {
        if (voice.isActive())
        {
            float tempBuff[256] = {0};

            voice.generateBlock(tempBuff, nFrames);

            for (int sample = 0; sample < nFrames; sample++)
                buff[sample] += tempBuff[sample];
        }
    }
}

