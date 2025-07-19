# MidiSynth

**MidiSynth** is a simple, real-time polyphonic synthesizer built in C++ using [RtAudio](https://github.com/thestk/rtaudio) and [RtMidi](https://github.com/thestk/rtmidi). It supports MIDI input, oscillator-based sound generation, and basic A(DS)R envelopes.

---

## Features

- Real-time audio and MIDI processing
- Sine wave oscillator
- Basic ADSR envelope (Attack & Release)
- Polyphonic voice management (multiple simultaneous notes)
- Modular design (Oscillator, Voice, VoiceManager, AudioEngine, SynthController)
- Designed with extensibility in mind (more waveforms, filters, and modulation to come)

---

## Architecture Overview
- **MidiInput**: Reads raw MIDI messages and forwards them.
- **SynthController**: Parses MIDI messages and routes them to the voice system.
- **VoiceManager**: Allocates voices and distributes note events.
- **Voice**: Combines oscillator + ADSR to render a note.
- **AudioEngine**: Pulls samples in real-time using `RtAudio`.

---

## Dependencies

- [RtAudio](https://github.com/thestk/rtaudio)
- [RtMidi](https://github.com/thestk/rtmidi)
- A C++17 compatible compiler

