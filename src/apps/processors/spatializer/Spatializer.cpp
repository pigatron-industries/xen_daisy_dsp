#include "Spatializer.h"

#include <math.h>

void Spatializer::init(float sampleRate) {
    this->sampleRate = sampleRate;
    delayLine.Init();
}

void Spatializer::process(float in) {
    delayLine.Write(in);
    float delay = delayLine.Read();
    if(pan > 0) {
        left = delay;
        right = in;
    } else {
        left = in;
        right = delay;
    }
}

void Spatializer::setPan(float pan) {
    this->pan = pan;
    float delaySamples = fabs(pan) * MAX_DELAY * sampleRate;
    delayLine.SetDelay(delaySamples > 1 ? delaySamples : 1);
}
