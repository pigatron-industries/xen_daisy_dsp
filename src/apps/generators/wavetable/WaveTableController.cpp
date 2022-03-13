#include "WaveTableController.h"
#include "modules/wavetable/WaveTableGenerator.h"

#define LEFT 0
#define RIGHT 1

void WaveTableController::init(float sampleRate) {
    Controller::init(sampleRate);

    for(int i = 0; i < 4; i++) {
        interpolator[i].init(Hardware::hw.permPool);
    }

    WaveTableFactory::addSine(&interpolator[0], 0.5);
    WaveTableFactory::addViolin(&interpolator[1], 0.5);
    WaveTableFactory::addSquare(&interpolator[2], 0.5);
    WaveTableFactory::addRamp(&interpolator[3], 0.5);

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
        float value = interpolationInput.getValue();
        interpolator.setInterpolation(value);
    }
}
