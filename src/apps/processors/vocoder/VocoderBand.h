#ifndef VocoderBand_h
#define VocoderBand_h

#include <DaisyDuino.h>
#include "../../../modules/StateVariableFilter.h"
#include "../../../modules/Oscillator.h"
#include "../../../modules/BiquadFilter.h"
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

    private:
        StateVariableFilter modulatorFilter;
        EnvelopeFollower envelopeFollower;
        StateVariableFilter carrierFilter;
        pigatron::Oscillator carrierOscillator;
        bool useCarrierOscillator = false;

};


inline float VocoderBand::process(float modulatorIn, float carrierIn) {
    modulatorFilter.process(modulatorIn);
    float mod = modulatorFilter.band();
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
