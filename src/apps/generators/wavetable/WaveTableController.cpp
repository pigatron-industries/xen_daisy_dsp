#include "WaveTableController.h"
#include "modules/wavetable/WaveTableGenerator.h"

#define LEFT 0
#define RIGHT 1

void WaveTableController::init(float sampleRate) {
    Controller::init(sampleRate);

    wavetable1.init(Hardware::hw.permPool);
    WaveTableFactory::addSquare(&wavetable1, 0.5);

    // wavetable2.init(sampleRate, TABLE_SIZE, 10, Hardware::hw.permPool);
    // WaveTableGenerator::addSine(wavetable2, 0.5);

    // wavetable3.init(sampleRate, TABLE_SIZE, 10, Hardware::hw.permPool);
    // WaveTableGenerator::addRamp(wavetable3, 0.5);

    // wavetable4.init(sampleRate, TABLE_SIZE, 10, Hardware::hw.permPool);
    // WaveTableGenerator::addViolin(wavetable4, 0.5);

    oscillator.init(sampleRate);

    displayPage.initTitle("Wave Table", "TABL");
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
        //Serial.println(interpolationInput.getValue());
        //oscillator.setInterpolation(interpolationInput.getValue());
    }
}
