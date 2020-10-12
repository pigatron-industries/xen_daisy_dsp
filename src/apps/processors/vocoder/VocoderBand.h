#ifndef VocoderBand_h
#define VocoderBand_h

#include "DaisyDuino.h"
#include "EnvelopeFollower.h"

class VocoderBand {
    public:
        VocoderBand() {}
        void init(float sampleRate);
        float process(float modulatorIn, float carrierIn);

        void setFrequency(float frequency);
        void setResonance(float resonance);
        void setUseCarrierOscillator(bool value) { useCarrierOscillator = value; }

    private:
        Svf modulatorFilter;
        EnvelopeFollower envelopeFollower;
        Svf carrierFilter;
        Oscillator carrierOscillator;
        bool useCarrierOscillator = false;

};

#endif
