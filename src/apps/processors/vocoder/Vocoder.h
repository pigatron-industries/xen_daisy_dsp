#ifndef Vocoder_h
#define Vocoder_h

#include "VocoderBand.h"

#define MAX_VOCODER_BANDS 31
#define MIN_VOCODER_BANDS 1

class Vocoder {
    public:
        Vocoder() {}
        void init(float sampleRate);
        float process(float modulatorIn, float carrierIn);

        void initBandsByBaseFrequency(float baseFrequency, float pitchInterval, int bandCount);
        void initBandsByCentreFrequency(float centreFrequency, float pitchInterval, int bandCount);

        void setResonance(float resonance);
        void setCarrierOscillator(deprecated::WaveTable& wavetable);
        void setUseCarrierOscillator(bool userCarrier);

        int getBandCount() { return bandCount; }
        float getPitchInterval() { return pitchInterval; }
        float getBaseFrequency() { return baseFrequency; }

        float getOddOutput() { return odd; }
        float getEvenOutput() { return even; }
        float getAllOutput() { return all; }

        VocoderBand* getBands() { return bands; }

    private:
        VocoderBand bands[MAX_VOCODER_BANDS];
        int bandCount;
        float pitchInterval;
        float frequencyRatio;
        float baseFrequency;

        float minFrequency = 27.5;
        float maxFrequency = 13289.75;

        float sampleRate;

        float odd, even, all;
};


inline float Vocoder::process(float modulatorIn, float carrierIn) {
    odd = 0;
    even = 0;
    for(int i = 0; i < bandCount; i++) {
        float out = bands[i].process(modulatorIn, carrierIn);
        if(i%2 == 0) {
            even += out;
        } else {
            odd += out;
        }
    }
    all = odd + even;
    return all;
}

#endif
