#ifndef Vocoder_h
#define Vocoder_h

#include "VocoderBand.h"

#define MAX_VOCODER_BANDS 20

class Vocoder {
    public:
        Vocoder() {}
        void init(float sampleRate);
        float process(float modulatorIn, float carrierIn);

        void initBands(float startFrequency, float pitchInterval, int bandCount);

        void setResonance(float resonance);
        void setFrequencyBase(float frequencyBase);
        void setPitchInterval(float pitchInterval);
        void setUseCarrierOscillator(bool value);

        int getBandCount() { return bandCount; }
        float getPitchInterval() { return pitchInterval; }
        float getFrequencyBase() { return frequencyBase; }

        float getOddOutput() { return odd; }
        float getEvenOutput() { return even; }
        float getAllOutput() { return all; }

    private:
        VocoderBand bands[MAX_VOCODER_BANDS];
        int bandCount;
        float pitchInterval, frequencyRatio;
        float frequencyBase;

        float sampleRate;

        float odd, even, all;
};


inline float Vocoder::process(float modulatorIn, float carrierIn) {
    all = 0;
    odd = 0;
    even = 0;
    for(int i = 0; i < bandCount; i++) {
        float out = bands[i].process(modulatorIn, carrierIn);
        all += out;
        if(i%2 == 0) {
            even += out;
        } else {
            odd += out;
        }
    }
    return all;
}

#endif
