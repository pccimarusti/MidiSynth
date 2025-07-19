//
// Created by Paul Cimarusti on 7/14/25.
//

#include "AudioEngine.h"

AudioEngine::AudioEngine(int nChannels_, float volume_) : audio(RtAudio::MACOSX_CORE), audioEngineEnabled(false), volume(volume_), buffSize(256), pISoundSource(nullptr) {
    output.deviceId = audio.getDefaultOutputDevice();
    output.nChannels = nChannels_;
}

void AudioEngine::SetSoundSource(ISoundSource* pISoundSource_) { pISoundSource = pISoundSource_; }

void AudioEngine::Start()
{
    std::cout << "\n--AUDIO ENGINE--\n STARTED\n";
    audio.openStream(&output, nullptr, RTAUDIO_FLOAT32, Constants::sampleRate, &buffSize, callBack, this);
    audio.startStream();
    audioEngineEnabled = true;
}

void AudioEngine::Stop()
{
    std::cout << "AUDIO ENGINE: STOPPED\n";
    audio.stopStream();
    audio.closeStream();
    audioEngineEnabled = false;
}

//void AudioEngine::SetVolume(float volume_) { volume = volume_; }

int AudioEngine::callBack(void *outBuf, void *, unsigned int nFrames, double, RtAudioStreamStatus, void *userData)
{
    // Uses reference to "this" to reference non-static members
    auto *engine = static_cast<AudioEngine*>(userData);
    auto *buf = static_cast<float*>(outBuf);

    ISoundSource* pSoundSourceThis = engine->pISoundSource;
    bool audioEnabledThis = engine->audioEngineEnabled;
    float volume = engine->volume;

    // Audio Engine is off or there is not a sound source
    if (!audioEnabledThis || !pSoundSourceThis) {
        std::cerr << "AUDIO ENGINE: CALLBACK WHILE VOID\n";
        for (unsigned int i = 0; i < nFrames; ++i)
            buf[i] = 0.0f;
        return 0;
    }

    // Writes output data
    // TODO: Multiply by volume
    pSoundSourceThis->generateBlock(buf, nFrames);

    return 0;
}