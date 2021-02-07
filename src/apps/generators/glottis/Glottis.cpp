#include "Glottis.h"
#include "modules/SimplexNoise.h"
#include "util/util.h"
#include <math.h>

void Glottis::init(float sampleRate) {
    this->sampleRate = sampleRate;
	timeStep = 1.0 / this->sampleRate;
    timeInWaveform = 0;
	frequency = 140;
    smoothFrequency = 140;
    targetFrequency = 140;
    oldTenseness = 0.6;
	newTenseness = 0.6;
	targetTenseness = 0.6;
	totalTime = 0.0;
	intensity = 0;
	loudness = 1;
	autoWobble = false;
	isTouched = false;
	alwaysVoice = true;
    setupWaveform();
}

float Glottis::process(float noiseSource) {
	this->timeInWaveform += timeStep;
	this->totalTime += timeStep;
	if (this->timeInWaveform > this->waveformLength)
	{
		this->timeInWaveform -= this->waveformLength;
		this->setupWaveform();
	}
	float out = this->normalizedLFWaveform(this->timeInWaveform / this->waveformLength);
	float aspiration = this->intensity * (1 - sqrt(this->targetTenseness)) * this->getNoiseModulator() * noiseSource;
	aspiration *= 0.2 + 0.02 * SimplexNoise::simplex1(this->totalTime * 1.99);
	out += aspiration;
	return out;
}

void Glottis::finishBlock() {
	if (this->targetFrequency > this->smoothFrequency)
		this->smoothFrequency = fmin(this->smoothFrequency * 1.1, this->targetFrequency);
	if (this->targetFrequency < this->smoothFrequency)
		this->smoothFrequency = fmax(this->smoothFrequency / 1.1, this->targetFrequency);
	this->frequency = this->smoothFrequency;

	this->oldTenseness = this->newTenseness;
	this->newTenseness = this->targetTenseness +
		0.1 * SimplexNoise::simplex1(this->totalTime * 0.46) + 0.05 * SimplexNoise::simplex1(this->totalTime * 0.36);
	if (!this->isTouched && alwaysVoice) this->newTenseness += (3-this->targetTenseness)*(1-this->intensity);
	
	if (this->isTouched || alwaysVoice) this->intensity += 0.13;
	else this->intensity -= 0.05;
	this->intensity = clamp(this->intensity, 0.0, 1.0);
}


void Glottis::setupWaveform() {
	finishBlock();

	float tenseness = this->newTenseness;
	this->rd = 3 * (1 - tenseness);
	this->waveformLength = 1.0 / this->frequency;
	
	float Rd = this->rd;
	if (Rd < 0.5) Rd = 0.5;
	if (Rd > 2.7) Rd = 2.7;
	float output;
	// normalized to time = 1, Ee = 1
	float Ra = -0.01 + 0.048 * Rd;
	float Rk = 0.224 + 0.118 * Rd;
	float Rg = (Rk / 4) * (0.5 + 1.2 * Rk) / (0.11 * Rd - Ra * (0.5 + 1.2 * Rk));
	
	float Ta = Ra;
	float Tp = 1 / (2.0 * Rg);
	float Te = Tp + Tp * Rk;
	
	float epsilon = 1 / Ta;
	float shift = exp(-epsilon * (1 - Te));
	float Delta = 1 - shift; //divide by this to scale RHS
	
	float RHSIntegral = (1 / epsilon) * (shift - 1) + (1 - Te) * shift;
	RHSIntegral = RHSIntegral / Delta;
	
	float totalLowerIntegral = - (Te-Tp) / 2.0 + RHSIntegral;
	float totalUpperIntegral = -totalLowerIntegral;
	
	float omega = M_PI / Tp;
	float s = sin(omega * Te);
	// need E0*e^(alpha*Te)*s = -1 (to meet the return at -1)
	// and E0*e^(alpha*Tp/2) * Tp*2/pi = totalUpperIntegral
	//             (our approximation of the integral up to Tp)
	// writing x for e^alpha,
	// have E0*x^Te*s = -1 and E0 * x^(Tp/2) * Tp*2/pi = totalUpperIntegral
	// dividing the second by the first,
	// letting y = x^(Tp/2 - Te),
	// y * Tp*2 / (pi*s) = -totalUpperIntegral;
	float y = -M_PI * s * totalUpperIntegral / (Tp * 2.0);
	float z = log(y);
	float alpha = z / (Tp / 2.0 - Te);
	float E0 = -1.0 / (s * exp(alpha*Te));
	this->alpha = alpha;
	this->e0 = E0;
	this->epsilon = epsilon;
	this->shift = shift;
	this->delta = Delta;
	this->te = Te;
	this->omega = omega;
}

float Glottis::getNoiseModulator(){
	float voiced = 0.1 + 0.2 * fmax(0.0, sin(M_PI * 2 * this->timeInWaveform / this->waveformLength));
	//return 0.3;
	return this->targetTenseness * this->intensity * voiced + (1 - this->targetTenseness * this->intensity) * 0.3;
}

float Glottis::normalizedLFWaveform(float t) {
	double output;
	if (t > this->te) {
        output = (-exp(-this->epsilon * (t - this->te)) + this->shift) / this->delta;
    } else {
        output = this->e0 * exp(this->alpha * t) * sin(this->omega * t);
    }
	return output * this->intensity * this->loudness;
}