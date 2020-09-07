#ifndef BiquadFilter_h
#define BiquadFilter_h

#include <inttypes.h>


class BiquadFilter {
    public:
        void init(float sampleRate);
        void setFrequency(float f);
        void setQ(float f);
        void setGain(float g);
        float process(float xn);

    private:
	    void updateCoefficients();
	
	    float frequency, q, gain;
	    float a0, a1, a2, b1, b2;
	    float xm1, xm2, ym1, ym2;
	    float sampleRate, twopiOverSampleRate;

};

#endif