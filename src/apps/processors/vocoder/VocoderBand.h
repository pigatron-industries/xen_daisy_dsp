#ifndef VocoderBand_h
#define VocoderBand_h

#include "modules/filters/StateVariableFilter.h"
#include "modules/filters/BiquadFilter.h"
#include "modules/oscillators/Oscillator.h"
#include "modules/wavetable/WaveTableOscillator.h"
#include "EnvelopeFollower.h"

using namespace pigatron;

#define TABLE_SIZE 256

class VocoderBand {
    public:
        VocoderBand() {}
        void init(float sampleRate);
        float process(float modulatorIn, float carrierIn);

        void setFrequency(float frequency);
        void setResonance(float resonance);
        void setCarrierOscillator(WaveTable* wavetable);

        float getFrequency() { return modulatorFilter.getFrequency(); }

    private:
        BiquadFilter modulatorFilter;
        EnvelopeFollower envelopeFollower;
        BiquadFilter carrierFilter;
        WaveTableOscillator carrierOscillator;
        bool useCarrierOscillator = false;

};


inline float VocoderBand::process(float modulatorIn, float carrierIn) {
    float mod = modulatorFilter.process(modulatorIn);
    float env = envelopeFollower.process(mod);

    if(useCarrierOscillator) {
        float osc = carrierOscillator.process();
        return osc * env;
    } else {
        float car = carrierFilter.process(carrierIn);
        return car * env;
    }
}


#endif
