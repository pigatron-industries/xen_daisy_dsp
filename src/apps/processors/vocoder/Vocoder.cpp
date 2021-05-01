#include "Vocoder.h"

#define HALF_OCTAVE_DOWN 0.7071067812  // 1/(2^0.5)
#define ONE_OCTAVE_DOWN 0.5

void Vocoder::init(float sampleRate) {
    for(int i = 0; i < MAX_VOCODER_BANDS; i++) {
        bands[i].init(sampleRate);
    }
}

void Vocoder::initBandsByBaseFrequency(float baseFrequency, float pitchInterval, int bandCount) {
    this->pitchInterval = pitchInterval;
    this->baseFrequency = baseFrequency;
    this->bandCount = bandCount;
    frequencyRatio = powf(2, pitchInterval);

    float frequency = baseFrequency;
    for(int i = 0; i < bandCount; i++) {
        bands[i].setFrequency(frequency);
        frequency = frequency * frequencyRatio;
    }
}

void Vocoder::initBandsByCentreFrequency(float centreFrequency, float pitchInterval, int bandCount) {
    float halfBandsInterval = pitchInterval * float(bandCount-1) * 0.5;
    float baseFrequency = centreFrequency * powf(2, -halfBandsInterval);
    initBandsByBaseFrequency(baseFrequency, pitchInterval, bandCount);
}

void Vocoder::setResonance(float resonance) {
    for(int i = 0; i < bandCount; i++) {
        bands[i].setResonance(resonance);
    }
}

void Vocoder::setCarrierOscillator(WaveTable* wavetable) {
    for(int i = 0; i < MAX_VOCODER_BANDS; i++) {
        bands[i].setCarrierOscillator(wavetable);
    }
}
