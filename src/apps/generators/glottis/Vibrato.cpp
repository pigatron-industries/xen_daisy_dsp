#include "Vibrato.h"

#include "../../../modules/SimplexNoise.h"
#include "../../../util/util.h"
#include <math.h>

void Vibrato::init(float sampleRate) {
    this->sampleRate = sampleRate;
    this->timeStep = 1.0 / this->sampleRate;
    vibratoAmount = 0.005;
	vibratoFrequency = 6;
	noiseAmount = 1;
}

float Vibrato::process(float lambda) {
	this->totalTime += timeStep;
    value = this->oldValue * (1 - lambda) + this->newValue * lambda;
    return value;
}

void Vibrato::update() {
    float vibrato = 0;
	vibrato += 0.01 * sinf(2 * M_PI * this->totalTime * this->vibratoFrequency);
	vibrato += 0.02 * SimplexNoise::simplex1(this->totalTime * 4.07) * this->noiseAmount;
	vibrato += 0.04 * SimplexNoise::simplex1(this->totalTime * 2.15) * this->noiseAmount;
	vibrato *= this->vibratoAmount;
	this->oldValue = this->newValue;
	this->newValue = this->targetValue * (1 + vibrato);
	if(totalTime >= M_PI*20) {
		totalTime -= M_PI*20;
	}
}
