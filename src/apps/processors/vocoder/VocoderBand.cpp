#include "VocoderBand.h"

void VocoderBand::init(float sampleRate) {
    modulatorFilter.init(sampleRate);
    modulatorFilter.setType(BiquadFilter::FilterType::BANDPASS);
    modulatorFilter.setQ(1);
    carrierFilter.init(sampleRate);
    envelopeFollower.init(sampleRate);
    carrierOscillator.init(sampleRate);
    carrierOscillator.setWaveform(pigatron::Oscillator::WAVE_TRI);
    carrierOscillator.setAmp(0.5);
}

void VocoderBand::setFrequency(float frequency) {
    modulatorFilter.setFrequency(frequency);
    carrierFilter.setFrequency(frequency);
    carrierOscillator.setFrequency(frequency);
}

void VocoderBand::setResonance(float resonance) {
    carrierFilter.setResonance(resonance);
}
