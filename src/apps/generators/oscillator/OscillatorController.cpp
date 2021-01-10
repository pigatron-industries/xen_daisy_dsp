#include "OscillatorController.h"

#define LEFT 0
#define RIGHT 1

void OscillatorController::init(float sampleRate) {
    oscillator.Init(sampleRate);
    oscillator.SetWaveform(Oscillator::WAVE_POLYBLEP_SQUARE);

    displayPage.initTitle("Oscillator", "OSC ");
}

void OscillatorController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        out[LEFT][i] = oscillator.Process();
        out[RIGHT][i] = out[LEFT][i];
    }
}

void OscillatorController::update() {
    pitchInput.update();
    oscillator.SetFreq(pitchInput.getValue());
}