#include "Vocoder.h"

void Vocoder::init(float sampleRate) {
    for(int i = 0; i < MAX_VOCODER_BANDS; i++) {
        bands[i].init(sampleRate);
    }
}

void Vocoder::initBands(float frequencyBase, float pitchInterval, int bandCount) {
    this->pitchInterval = pitchInterval;
    this->frequencyBase = frequencyBase;
    this->bandCount = bandCount;
    frequencyRatio = powf(2, pitchInterval);

    float frequency = frequencyBase;
    for(int i = 0; i < bandCount; i++) {
        bands[i].setFrequency(frequency);
        frequency = frequency * frequencyRatio;
    }
}

void Vocoder::setResonance(float resonance) {
    for(int i = 0; i < bandCount; i++) {
        bands[i].setResonance(resonance);
    }
}

void Vocoder::setFrequencyBase(float frequencyBase) {
    this->frequencyBase = frequencyBase;
    float frequency = frequencyBase;
    float pitch = 0;
    for(int i = 0; i < bandCount; i++) {
        bands[i].setFrequency(frequency);
        frequency = frequency * frequencyRatio;
    }
}

void Vocoder::setPitchInterval(float pitchInterval) {
    this->pitchInterval = pitchInterval;
    frequencyRatio = powf(2, pitchInterval);

    float frequency = frequencyBase;
    for(int i = 0; i < bandCount; i++) {
        bands[i].setFrequency(frequency);
        frequency = frequency * frequencyRatio;
    }
}

void Vocoder::setUseCarrierOscillator(bool value) {
    for(int i = 0; i < bandCount; i++) {
        bands[i].setUseCarrierOscillator(value);
    }
}

float Vocoder::process(float modulatorIn, float carrierIn) {
    float out = 0;
    for(int i = 0; i < bandCount; i++) {
        out += bands[i].process(modulatorIn, carrierIn);
    }
    return out;
}

