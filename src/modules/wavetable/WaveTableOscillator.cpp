#include "WaveTableOscillator.h"

void WaveTableOscillator::init(float sampleRate, int tableSize, int tableCount) {
    this->sampleRate = sampleRate;
    this->tableSize = tableSize;
    this->tableCount = tableCount;
    this->sampleRateReciprocal = 1/sampleRate;
}

void WaveTableOscillator::setFrequency(float frequency) { 
    this->frequency = frequency;
    increment = (tableSize * frequency) * sampleRateReciprocal;
}

float WaveTableOscillator::process() {
    position += increment;
    if(position > tableSize-1) {
        position -= tableSize-1;
    }

    int index = static_cast<int>(interpolation);
    if(index < tableCount-1) {
        float fraction = interpolation - static_cast<float>(index);
        float a = wavetables[index]->read(position);
        float b = wavetables[index+1]->read(position);
        return a + (b - a) * fraction;
    } else {
        return wavetables[tableCount-1]->read(position);
    }
}
