#include "AllPass.h"

#include "../../util/util.h"

void AllPass::init(float sampleRate) {
    gain = 1;
    frequency = 440;
    this->sampleRate = sampleRate;
    calcCoefficient();
}

void AllPass::setGain(float gain) {
    this->gain = gain;
    calcCoefficient();
}

void AllPass::setFrequency(float frequency) {
    this->frequency = frequency;
    calcCoefficient();
}

void AllPass::calcCoefficient() {
    if(gain >= 1 || gain <= -1) {
        coefficient = (tanf(M_PI * frequency / sampleRate) - 1) / (tanf(M_PI * frequency / sampleRate) + 1);
    } else if (gain >= 0) {
        coefficient = (tanf(M_PI * frequency / sampleRate) - gain) / (tanf(M_PI * frequency / sampleRate) + gain);
    } else {
        coefficient = (-gain * tanf(M_PI * frequency / sampleRate) - 1) / (-gain * tanf(M_PI * frequency / sampleRate) + 1);
    }
}
