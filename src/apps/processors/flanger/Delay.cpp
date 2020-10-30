#include "Delay.h"
#include "../../../io/MemPool.h"

void Delay::init(float sampleRate) {
    this->sampleRate = sampleRate;
    delayLine = new (MemPool::allocate(sizeof(DelayLine<float, MAX_DELAY>))) DelayLine<float, MAX_DELAY>();
    delayLine->Init();
}

float Delay::process(float in) {
        float wet = delayLine->Read();

        // feedback
        float feedback = wet * feedbackLevel;
        if(invertedFeedback) {
            feedback = -feedback;
        }

        delayLine->Write(in+feedback);
        return in * dryLevel + wet * wetLevel;
}

void Delay::setDelay(float delayTime) {
    float delaySamples = delayTime * sampleRate;
    delayLine->SetDelay(delaySamples);
}
