#ifndef VocoderBand_h
#define VocoderBand_h

#include "modules/filters/StateVariableFilter.h"
#include "modules/filters/BiquadFilter.h"
#include "modules/oscillators/Oscillator.h"
#include "EnvelopeFollower.h"

using namespace pigatron;

class VocoderBand {
    public:
        VocoderBand() {}
        void init(float sampleRate);
        float process(float modulatorIn, float carrierIn);

        void setFrequency(float frequency);
        void setResonance(float resonance);
        void setUseCarrierOscillator(bool value) { useCarrierOscillator = value; }

        float getFrequency() { return modulatorFilter.getFrequency(); }

    private:
        BiquadFilter modulatorFilter;
        EnvelopeFollower envelopeFollower;
        StateVariableFilter carrierFilter;
        pigatron::Oscillator carrierOscillator;
        bool useCarrierOscillator = false;

};


inline float VocoderBand::process(float modulatorIn, float carrierIn) {
    float mod = modulatorFilter.process(modulatorIn);
    float env = envelopeFollower.process(mod);

    if(useCarrierOscillator) {
        float osc = carrierOscillator.process();
        return osc * env;
    } else {
        carrierFilter.process(carrierIn);
        float car = carrierFilter.band();
        return car * env;
    }
}


#endif
