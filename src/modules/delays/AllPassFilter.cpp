#include "AllPassFilter.h"

void AllPassFilter::init(float sampleRate, float maxDelay) {
    delay.init(sampleRate, maxDelay);
    delay.setDelayTime(maxDelay);
}

void AllPassFilter::setDelayTime(float delayTime) {
    delay.setDelayTime(delayTime);
}
