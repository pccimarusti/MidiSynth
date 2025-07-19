//
// Created by Paul Cimarusti on 7/14/25.
//

#ifndef MIDISYNTH_AUDIOENGINE_H
#define MIDISYNTH_AUDIOENGINE_H


#include "RtAudio.h"
#include "../Interfaces/ISoundSource.h"
#include "../Constants.h"

// @brief manages all audio output with rtaudio's callback
class AudioEngine
{
public:
    AudioEngine(int nChannels_, float volume_);
    void SetSoundSource(ISoundSource* pISoundSource_);
    void Start();
    void Stop();
//    void SetVolume(float volume_);

private:
    RtAudio audio;
    RtAudio::StreamParameters output;
    ISoundSource* pISoundSource;

    static int callBack(void *outBuf, void *, unsigned int nFrames, double, RtAudioStreamStatus, void *);
    unsigned int buffSize;
    bool audioEngineEnabled;
    float volume;
};


#endif //MIDISYNTH_AUDIOENGINE_H
