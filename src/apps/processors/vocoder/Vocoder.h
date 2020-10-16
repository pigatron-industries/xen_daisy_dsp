#ifndef Vocoder_h
#define Vocoder_h

#include "VocoderBand.h"

#define MAX_VOCODER_BANDS 18

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

    private:
        VocoderBand bands[MAX_VOCODER_BANDS];
        int bandCount;
        float pitchInterval, frequencyRatio;
        float frequencyBase;

        float sampleRate;

};

#endif
