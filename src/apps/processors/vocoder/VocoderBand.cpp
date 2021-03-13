#include "VocoderBand.h"

void VocoderBand::init(float sampleRate) {
    modulatorFilter.init(sampleRate);
    modulatorFilter.setType(BiquadFilter::FilterType::BANDPASS);
    modulatorFilter.setQ(1);
    carrierFilter.init(sampleRate);
    carrierFilter.setType(BiquadFilter::FilterType::BANDPASS);
    carrierFilter.setQ(1);
    envelopeFollower.init(sampleRate);
    carrierOscillator.init(sampleRate, TABLE_SIZE);
}

void VocoderBand::setFrequency(float frequency) {
    modulatorFilter.setFrequency(frequency);
    carrierFilter.setFrequency(frequency);
    carrierOscillator.setFrequency(frequency);
}

void VocoderBand::setResonance(float resonance) {
    carrierFilter.setQ(resonance);
}

void VocoderBand::setCarrierOscillator(WaveTable* wavetable) { 
    if(wavetable != NULL) {
        useCarrierOscillator = true;
        carrierOscillator.setWaveTable(0, wavetable);
    } else {
        useCarrierOscillator = false;
    }
}
