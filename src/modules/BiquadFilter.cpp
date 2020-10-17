#include "BiquadFilter.h"
#include <math.h>


void BiquadFilter::init(float _sampleRate) {
    frequency = 500;
    q = 0.5;
    gain = 1;
    xm1 = 0.0;
    xm2 = 0.0;
    ym1 = 0.0;
    ym2 = 0.0;
    sampleRate = _sampleRate;
    twopiOverSampleRate = M_PI * 2.0 / this->sampleRate;
    updateCoefficients();
}

void BiquadFilter::updateCoefficients() {
	float omega = this->frequency * this->twopiOverSampleRate;
	float sn = sin(omega);
	float cs = cos(omega);
	float one_over_Q = 1./this->q;
	float alpha = sn * 0.5 * one_over_Q;
	
	// Bandpass only, for now
	float b0 = 1./(1. + alpha);
	this->a0 = alpha * b0;
	this->a1 = 0.;
	this->a2 = -alpha * b0;
	this->b1 = -2. * cs * b0;
	this->b2 = (1. - alpha) * b0;
}

void BiquadFilter::setFrequency(float f) {
	this->frequency = f;
	this->updateCoefficients();
}

void BiquadFilter::setGain(float g) {
	this->gain = g;
	this->updateCoefficients();
}

void BiquadFilter::setQ(float q) {
	this->q = q;
	this->updateCoefficients();
}
