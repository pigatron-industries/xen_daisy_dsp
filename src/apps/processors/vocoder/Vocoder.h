#ifndef Vocoder_h
#define Vocoder_h

#include "VocoderBand.h"

#define MAX_VOCODER_BANDS 18

class Vocoder {
    public:
        Vocoder() {}
        void init(float sampleRate);
        float process(float modulatorIn, float carrierIn);

        void initBands(float startFrequency, float pitchDifference, float octaves);

        void setResonance(float resonance);
        void setUseCarrierOscillator(bool value);

        int getBandCount() { return bandCount; }

    private:
        VocoderBand bands[MAX_VOCODER_BANDS];
        int bandCount;

        float sampleRate;

};

#endif
