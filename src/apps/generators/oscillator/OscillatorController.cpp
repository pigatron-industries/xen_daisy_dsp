#include "OscillatorController.h"

#define LEFT 0
#define RIGHT 1

void OscillatorController::init(float sampleRate) {
    oscillator.init(sampleRate);
    oscillator.setPolyblep(true);
    displayPage.initTitle("Oscillator", "OSC ");
}

void OscillatorController::update() {
    if(pitchInput.update()) {
        oscillator.setFrequency(pitchInput.getValue());
    }
    if(waveInput.update()) {
        float value = waveInput.getValue();
        if(value < 1) {
            waveSelector.select(0);
        } else if (value < 2) {
            waveSelector.select(1);
        } else if (value < 3) {
            waveSelector.select(2);
        } else if (value < 4) {
            waveSelector.select(3);
        }
    }
}

void OscillatorController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        out[LEFT][i] = oscillator.process();
        out[RIGHT][i] = out[LEFT][i];
    }
}