#include "WaveTableOscillator.h"

using namespace deprecated;

void WaveTableOscillator::init(float sampleRate, int tableSize) {
    this->sampleRate = sampleRate;
    this->tableSize = tableSize;
    this->tableCount = 0;
    this->sampleRateReciprocal = 1/sampleRate;
    this->interpolation = 0.0;
}

void WaveTableOscillator::setWaveTable(int index, WaveTable& wavetable) {
    wavetables[index] = &wavetable;
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
