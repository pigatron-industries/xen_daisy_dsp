#include "WaveTableController.h"
#include "WaveTableGenerator.h"

#define LEFT 0
#define RIGHT 1

void WaveTableController::init(float sampleRate) {
    wavetable.init(sampleRate, (size_t)sampleRate);
    WaveTableGenerator::sine(wavetable);
    displayPage.initTitle("Oscillator");
}

void WaveTableController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        out[LEFT][i] = wavetable.process();
        out[RIGHT][i] = out[LEFT][i];
    }
}

void WaveTableController::update() {
    pitchInput.update();
    wavetable.setFrequency(pitchInput.getFrequency());
}
