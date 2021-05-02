#include "Normalizer.h"

#include <math.h>

void Normalizer::init(int sampleSize, float targetAmplitude, float maxGain) {
    this->sampleSize = sampleSize;
    this->maxGain = maxGain;
    this->targetAmplitude = targetAmplitude;
    sampleCounter = 0;
    maxSample = 0;
    gain = 1;
}

float Normalizer::process(float in) {
    float absIn = fabs(in);
    if(absIn > maxSample) {
        maxSample = absIn;
    }

    sampleCounter++;
    if(sampleCounter == sampleSize) {
        float newGain = targetAmplitude/maxSample;
        if(newGain < maxGain) {
            gain = newGain;
        }
        maxSample = 0;
        sampleCounter = 0;
    }

    return in * gain;
}