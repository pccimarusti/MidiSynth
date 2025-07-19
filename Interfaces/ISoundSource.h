//
// Created by Paul Cimarusti on 7/17/25.
//

#ifndef MIDISYNTH_ISOUNDSOURCE_H
#define MIDISYNTH_ISOUNDSOURCE_H


class ISoundSource
{
public:
    virtual ~ISoundSource() = default;
    virtual void noteOn(int note, int velocity) = 0;
    virtual void noteOff(int note) = 0;
    virtual void generateBlock(float* buff, unsigned int nFrames) = 0;
};


#endif //MIDISYNTH_ISOUNDSOURCE_H
