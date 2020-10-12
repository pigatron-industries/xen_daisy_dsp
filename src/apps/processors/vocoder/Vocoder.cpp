#include "Vocoder.h"

void Vocoder::init(float sampleRate) {
    for(int i = 0; i < MAX_VOCODER_BANDS; i++) {
        bands[i].init(sampleRate);
    }
}

void Vocoder::initBands(float startFrequency, float pitchDifference, float octaves) {
    float frequencyRatio = powf(2, pitchDifference);
    float frequency = startFrequency;
    float pitch = 0;
    bandCount = MAX_VOCODER_BANDS;
    for(int i = 0; i < MAX_VOCODER_BANDS; i++) {
        bands[i].setFrequency(frequency);
        frequency = frequency * frequencyRatio;
        pitch = pitch + pitchDifference;
        if(pitch > octaves) {
            bandCount = i;
            break;
        }
    }
}

void Vocoder::setResonance(float resonance) {
    for(int i = 0; i < bandCount; i++) {
        bands[i].setResonance(resonance);
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

