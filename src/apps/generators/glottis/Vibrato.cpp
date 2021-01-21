#include "Vibrato.h"

#include "../../../modules/SimplexNoise.h"
#include "../../../util/util.h"
#include <math.h>

void Vibrato::init(float sampleRate) {
    sampleRate = sampleRate;
    timeStep = 1.0 / sampleRate;
    vibratoAmount = 0.005;
	vibratoFrequency = 6;
	noiseAmount = 1;
	updatePeriod = 0.001;
	lambdaStep = timeStep/updatePeriod;
}

float Vibrato::process() {
	totalTime += timeStep;
	lambda += lambdaStep;
	if(lambda >= 1) {
		update();
	}
	
	value = oldValue * (1 - lambda) + newValue * lambda;
    return value;
}

void Vibrato::update() {
    float vibrato = 0;
	vibrato += 0.01 * sinf(2 * M_PI * totalTime * vibratoFrequency);
	vibrato += 0.02 * SimplexNoise::simplex1(totalTime * 4.07) * noiseAmount;
	vibrato += 0.04 * SimplexNoise::simplex1(totalTime * 2.15) * noiseAmount;
	vibrato *= vibratoAmount;
	oldValue = newValue;
	newValue = targetValue * (1 + vibrato);
	if(totalTime >= M_PI*20) {
		totalTime -= M_PI*20;
	}
	lambda = 0;
}
