#include "WaveTableController.h"
#include "modules/wavetable/WaveTableGenerator.h"

#define LEFT 0
#define RIGHT 1

void WaveTableController::init(float sampleRate) {
    Controller::init(sampleRate);

    wavetable1.init(Hardware::hw.permPool);
    WaveTableFactory::addSquare(&wavetable1, 0.5);

    wavetable2.init(Hardware::hw.permPool);
    WaveTableFactory::addSine(&wavetable2, 0.5);

    wavetable3.init(Hardware::hw.permPool);
    WaveTableFactory::addRamp(&wavetable3, 0.5);

    wavetable4.init(Hardware::hw.permPool);
    WaveTableFactory::addViolin(&wavetable4, 0.5);

    selector.select(0);

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
        selector.select(int(value));
    }
}
