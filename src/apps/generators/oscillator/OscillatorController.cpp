#include "OscillatorController.h"

#define LEFT 0
#define RIGHT 1

void OscillatorController::init(float sampleRate) {
    oscillator.init(sampleRate);
    oscillator.setWaveform(pigatron::Oscillator::WAVE_POLYBLEP_SQUARE);
    displayPage.initTitle("Oscillator", "OSC ");
}

void OscillatorController::update() {
    pitchInput.update();
    oscillator.setFrequency(pitchInput.getValue());
}

void OscillatorController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        out[LEFT][i] = oscillator.process();
        out[RIGHT][i] = out[LEFT][i];
    }
}