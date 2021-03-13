#ifndef WaveTableOscillator_h
#define WaveTableOscillator_h

#include "WaveTable.h"

#define MAX_WAVETABLE_COUNT 10

class WaveTableOscillator {
    public:
        WaveTableOscillator() {}
        void init(float sampleRate, int tableSize);
        float process();

        void setWaveTable(int index, WaveTable* wavetable);
        void setFrequency(float frequency);
        void setInterpolation(float interpolation) { this->interpolation = interpolation; }
        void setPhase(float phase) { position = float(tableSize) * phase; }

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

inline float WaveTableOscillator::process() {
    int index = static_cast<int>(interpolation);
    float output = 0;
    if(index < tableCount-1) {
        float fraction = interpolation - static_cast<float>(index);
        float a = wavetables[index]->read(position);
        float b = wavetables[index+1]->read(position);
        output = a + (b - a) * fraction;
    } else {
        output = wavetables[tableCount-1]->read(position);
    }

    position += increment;
    if(position > tableSize-1) {
        position -= tableSize-1;
    }

    return output;
}

#endif