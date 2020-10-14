#include "VocoderBand.h"

void VocoderBand::init(float sampleRate) {
    modulatorFilter.Init(sampleRate);
    carrierFilter.Init(sampleRate);
    envelopeFollower.init(sampleRate);
    carrierOscillator.Init(sampleRate);
    carrierOscillator.SetWaveform(pigatron::Oscillator::WAVE_SIN);
    carrierOscillator.SetAmp(0.5);
}

void VocoderBand::setFrequency(float frequency) {
    modulatorFilter.SetFreq(frequency);
    carrierFilter.SetFreq(frequency);
    carrierOscillator.SetFreq(frequency);
}

void VocoderBand::setResonance(float resonance) {
    carrierFilter.SetRes(resonance);
}

float VocoderBand::process(float modulatorIn, float carrierIn) {
    modulatorFilter.Process(modulatorIn);
    float mod = modulatorFilter.Band();
    float env = envelopeFollower.process(mod);

    if(useCarrierOscillator) {
        float osc = carrierOscillator.Process();
        return osc * env;
    } else {
        carrierFilter.Process(carrierIn);
        float car = carrierFilter.Band();
        return car * env;
    }
}
