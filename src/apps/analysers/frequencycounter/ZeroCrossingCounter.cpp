#include "ZeroCrossingCounter.h"
#include "util/util.h"

#define THRESHOLD 0.1

void ZeroCrossingCounter::init(float sampleRate) {
    this->sampleRate = sampleRate;
    sampleRateRecip = 1 / sampleRate;
}

void ZeroCrossingCounter::process(float in) {
    sampleCount++;
    if(in > THRESHOLD && lastSign == NEGATIVE) {
        timeSamples = sampleCount;
        time = timeSamples * sampleRateRecip;
        smoothedTime = smooth(time, smoothedTime, 0.2);
        sampleCount = 0;
    }

    if(in > THRESHOLD) {
        lastSign = POSITIVE;
    } else if (in < -THRESHOLD) {
        lastSign = NEGATIVE;
    }
}

float ZeroCrossingCounter::getFrequency() {
    return 1 / time;
}
