#include "WaveTableOscillator.h"

void WaveTableOscillator::init(float sampleRate, int tableSize) {
    this->sampleRate = sampleRate;
    this->tableSize = tableSize;
    this->tableCount = 0;
    this->sampleRateReciprocal = 1/sampleRate;
}

void WaveTableOscillator::setWaveTable(int index, WaveTable* wavetable) {
    wavetables[index] = wavetable;
    if(tableCount <= index) {
        tableCount = index+1;
    }
}

void WaveTableOscillator::setFrequency(float frequency) { 
    this->frequency = frequency;
    increment = (tableSize * frequency) * sampleRateReciprocal;
    for(int i = 0; i < tableCount; i++) {
        wavetables[i]->setFrequencyTable(frequency);
    }
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
