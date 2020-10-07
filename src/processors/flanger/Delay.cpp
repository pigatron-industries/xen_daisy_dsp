#include "Delay.h"

void Delay::init(float sampleRate) {
    this->sampleRate = sampleRate;
}

float Delay::process(float in) {
        float wet = delayLine.Read();

        // feedback
        float feedback = wet * feedbackLevel;
        if(invertedFeedback) {
            feedback = -feedback;
        }

        delayLine.Write(in+feedback);
        return in * dryLevel + wet * wetLevel;
}

void Delay::setDelay(float delayTime) {
    float delaySamples = delayTime * sampleRate;
    delayLine.SetDelay(delaySamples);
}
