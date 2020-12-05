#include "WaveTableController.h"
#include "WaveTableGenerator.h"

#define LEFT 0
#define RIGHT 1

void WaveTableController::init(float sampleRate) {
    wavetable1.init(sampleRate, (size_t)sampleRate);
    WaveTableGenerator::square(wavetable1, 0.5, 0.5);

    wavetable2.init(sampleRate, (size_t)sampleRate);
    WaveTableGenerator::sine(wavetable2, 0.5);

    oscillator.init(sampleRate, (size_t)sampleRate, 2);
    oscillator.setWaveTable(0, &wavetable1);
    oscillator.setWaveTable(1, &wavetable2);

    displayPage.initTitle("Oscillator");
}

void WaveTableController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        out[LEFT][i] = oscillator.process();
        out[RIGHT][i] = out[LEFT][i];
    }
}

void WaveTableController::update() {
    pitchInput.update();
    interpolationInput.update();
    wavetable1.setFrequency(pitchInput.getFrequency());
    oscillator.setFrequency(pitchInput.getFrequency());
    oscillator.setInterpolation(interpolationInput.getValue());
}
