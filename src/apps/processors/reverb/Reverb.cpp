#include "Reverb.h"

void Reverb::init(float sampleRate) {
    this->sampleRate = sampleRate;
    multitapDelay.init(sampleRate, 10.0);
    multitapDelay.createTaps(10, 1, 0.8, 0.5);
}

float Reverb::process(float in) {
    return multitapDelay.process(in);
}