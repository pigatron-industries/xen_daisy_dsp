#include "MultitapDelay.h"

void MultitapDelay::init(float sampleRate, float maxDelay) {
    this->sampleRate = sampleRate;
    delayLine.init(sampleRate*maxDelay);
}

void MultitapDelay::setTap(int tapIndex, float delayTime, float tapGain) {
    tapPositions[tapIndex] = delayTime*sampleRate;
    tapGains[tapIndex] = tapGain;
}

float MultitapDelay::process(float in) {
    float output = 0.0;
    for(int i = 0; i < tapCount; i++) {
        output += delayLine.read(tapPositions[i]) * tapGains[i];
    }

    delayLine.write(in);
    return output + in*0.2;
}
