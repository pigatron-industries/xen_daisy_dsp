#include "WaveTableController.h"
#include "WaveTableGenerator.h"

#define LEFT 0
#define RIGHT 1

void WaveTableController::init(float sampleRate) {
    wavetable1.init(sampleRate, 1024);
    WaveTableGenerator::ramp(wavetable1, 0.5);

    wavetable2.init(sampleRate, 1024);
    WaveTableGenerator::sine(wavetable2, 0.5);

    oscillator.init(sampleRate, 1024, 2);
    oscillator.setWaveTable(0, &wavetable1);
    oscillator.setWaveTable(1, &wavetable2);

    displayPage.initTitle("Oscillator");
}

void WaveTableController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        float samp = oscillator.process();
        out[LEFT][i] = samp;
        out[RIGHT][i] = samp;
    }
}

void WaveTableController::update() {
    pitchInput.update();
    interpolationInput.update();
    wavetable1.setFrequency(pitchInput.getValue());
    oscillator.setFrequency(pitchInput.getValue());
    oscillator.setInterpolation(interpolationInput.getValue());
}
