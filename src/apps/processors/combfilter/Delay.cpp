#include "Delay.h"
#include "../../../io/MemPool.h"

void Delay::init(float sampleRate, float maxDelay) {
    this->sampleRate = sampleRate;
    this->maxDelay = maxDelay;
    delayLine.init(sampleRate * maxDelay);
}

float Delay::process(float in) {
        float wet = delayLine.read();
        float feedback = wet * feedbackLevel;
        delayLine.write(in+feedback);
        return in * dryLevel + wet * wetLevel;
}

void Delay::setDelay(float delayTime) {
    delayLine.setDelay(delayTime * sampleRate);
}
