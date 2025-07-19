#include "Midi/MidiInput.h"
#include "SynthController/SynthController.h"
#include "Audio/Oscillator.h"
#include "Audio/AudioEngine.h"
#include "Audio/VoiceManager.h"

int main()
{
    // -- Configuration --
    // Audio Engine Init
    AudioEngine audioEngine(1, 0.25);

    // Audio Oscillator Init / Config
    Oscillator osc;
    osc.setWaveType(Oscillator::WaveType::Sine);

    // Voice Manager Init / Config
    VoiceManager voiceManager;
    audioEngine.SetSoundSource(&voiceManager);

    // Synth Controller Init
    SynthController synthController(&voiceManager);

    // Midi Input Init
    MidiInput midiInput(&synthController);


    // -- Implementation --
    midiInput.connectUserInputMidiPort();

    audioEngine.Start();
    // Main Loop
    char input;
    while (true)
    {
        std::cout << "Listening for midi messages, press q to quit\n";
        std::cin >> input;
        if (input == 'q')
            break;
    }
    audioEngine.Stop();

    return 0;
}
