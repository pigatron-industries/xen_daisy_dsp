#include "AdditiveOscillatorController.h"

#define LEFT 0
#define RIGHT 1

void AdditiveOscillatorController::init(float sampleRate) {
    normalizer.init(4096);
    oscillator.init(sampleRate, OSCILLATOR_COUNT);
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        oscillator.setOscillator(i, i+1, 0);
    }

    displayPage.initTitle("Additive Oscillator", "ADDO");
}

void AdditiveOscillatorController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        out[LEFT][i] = normalizer.process(oscillator.process());
        out[RIGHT][i] = out[LEFT][i];
    }
}

void AdditiveOscillatorController::update() {
    for(int i = 0; i < OSCILLATOR_COUNT; i++) {
        if(amplitudeInputs[i].update()) {
            oscillator.setAmplitude(i, amplitudeInputs[i].getValue());
        }
    }

    if(frequencyInput.update()) {
        oscillator.setFrequency(frequencyInput.getValue());
    }
}
