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


inline float BiquadFilter::process(float xn) {
	float yn = (this->a0 * xn) + (this->a1 * this->xm1) + (this->a2 * this->xm2) - (this->b1 * this->ym1) - (this->b2 * this->ym2);
	this->ym2 = this->ym1;
	this->ym1 = yn;
	this->xm2 = this->xm1;
	this->xm1 = xn;
	return yn;
}

#endif