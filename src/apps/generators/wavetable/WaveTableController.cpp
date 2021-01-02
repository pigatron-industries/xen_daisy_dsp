#include "WaveTableController.h"
#include "../../../modules/wavetable/WaveTableGenerator.h"

#define LEFT 0
#define RIGHT 1

#define TABLE_SIZE 1024

void WaveTableController::init(float sampleRate) {
    wavetable1.init(sampleRate, TABLE_SIZE, 10);
    WaveTableGenerator::addSine(wavetable1, 0.5);

    wavetable2.init(sampleRate, TABLE_SIZE, 10);
    WaveTableGenerator::addTriangle(wavetable2, 0.5);

    wavetable3.init(sampleRate, TABLE_SIZE, 10);
    WaveTableGenerator::addSquare(wavetable3, 0.5);

    wavetable4.init(sampleRate, TABLE_SIZE, 10);
    WaveTableGenerator::addRamp(wavetable4, 0.5);

    oscillator.init(sampleRate, TABLE_SIZE);
    oscillator.setWaveTable(0, &wavetable1);
    oscillator.setWaveTable(1, &wavetable2);
    oscillator.setWaveTable(2, &wavetable3);
    oscillator.setWaveTable(3, &wavetable4);

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
        oscillator.setFrequency(pitchInput.getValue());
    }

    if(interpolationInput.update()) {
        Serial.println(interpolationInput.getValue());
        oscillator.setInterpolation(interpolationInput.getValue());
    }
}
