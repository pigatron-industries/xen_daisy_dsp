#include "WaveTableController.h"
#include "../../../modules/wavetable/WaveTableGenerator.h"

#define LEFT 0
#define RIGHT 1

#define TABLE_SIZE 1024

void WaveTableController::init(float sampleRate) {
    wavetable1.init(sampleRate, TABLE_SIZE, 10);
    WaveTableGenerator::blSquare(wavetable1, 0.5);

    wavetable2.init(sampleRate, TABLE_SIZE, 10);
    WaveTableGenerator::blSine(wavetable2, 0.5);

    oscillator.init(sampleRate, TABLE_SIZE, 2);
    oscillator.setWaveTable(0, &wavetable1);
    oscillator.setWaveTable(1, &wavetable2);

    displayPage.initTitle("Wave Table");
}

void WaveTableController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        float samp = oscillator.process();
        out[LEFT][i] = samp;
        out[RIGHT][i] = samp;
    }
}

void WaveTableController::update() {
    if(pitchInput.update()) {
        wavetable1.setFrequency(pitchInput.getValue());
        wavetable2.setFrequency(pitchInput.getValue());
        oscillator.setFrequency(pitchInput.getValue());
    }

    if(interpolationInput.update()) {
        oscillator.setInterpolation(interpolationInput.getValue());
    }
}
