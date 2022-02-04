#include "AdditiveOscillator.h"

void AdditiveOscillator::init(float sampleRate, int oscillatorCount) {
    for(int i = 0; i < MAX_OSCILLATORS; i++) {
        oscillator[i].init(sampleRate);
    }
    this->oscillatorCount = oscillatorCount;
    setFrequency(440);
}

void AdditiveOscillator::setOscillator(int index, float frequencyRatio, float amplitude, float phaseShift) {
    frequencyRatios[index] = frequencyRatio;
    oscillator[index].setFrequency(frequency * frequencyRatio);
    oscillator[index].setAmplitude(amplitude);
    oscillator[index].setPhase(phaseShift);
}

void AdditiveOscillator::setFrequency(float frequency) {
    this->frequency = frequency;
    for(int i = 0; i < oscillatorCount; i++) {
        oscillator[i].setFrequency(frequency * frequencyRatios[i]);
    }
}

void AdditiveOscillator::setAmplitude(int index, float amplitude) {
    oscillator[index].setAmplitude(amplitude);
}

float AdditiveOscillator::process() {
    float sample = 0;
    for(int i = 0; i < oscillatorCount; i++) {
        sample += oscillator[i].process();
    }
    return sample;
}
