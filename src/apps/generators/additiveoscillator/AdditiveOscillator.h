#ifndef AdditiveOscillator_h
#define AdditiveOscillator_h

#include "../../../modules/oscillators/Oscillator.h"

#define MAX_OSCILLATORS 20

class AdditiveOscillator {
    public:
        AdditiveOscillator() {}
        void init(float sampleRate, int oscillatorCount);
        float process();

        void setOscillator(int index, float frequencyRatio, float amplitude, float phaseShift = 0);
        void setFrequency(float frequency);
        void setAmplitude(int index, float amplitude);

    private:
        pigatron::Oscillator oscillator[MAX_OSCILLATORS];
        float frequencyRatios[MAX_OSCILLATORS];
        int oscillatorCount;

        float frequency;
};

#endif
