#ifndef WaveTableOscillator_h
#define WaveTableOscillator_h

#include "WaveTable.h"

#define MAX_WAVETABLE_COUNT 2

class WaveTableOscillator {
    public:
        WaveTableOscillator() {}
        void init(float sampleRate, int tableSize, int tableCount);
        float process();

        void setWaveTable(int index, WaveTable* wavetable) { wavetables[index] = wavetable; }
        void setFrequency(float frequency);
        void setInterpolation(float interpolation) { this->interpolation = interpolation; }

    private:
        WaveTable* wavetables[MAX_WAVETABLE_COUNT];
        int tableSize;
        int tableCount;

        float sampleRate;
        float sampleRateReciprocal;
        float position;
        float increment;
        float frequency;

        float interpolation;

        float process(int index);
};

#endif
