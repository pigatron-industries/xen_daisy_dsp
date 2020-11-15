#include "PhaserController.h"

#define LEFT 0
#define RIGHT 1

void PhaserController::init(float sampleRate) {
    this->sampleRate = sampleRate;
    filterLeft.init(sampleRate, 1.0);
    filterRight.init(sampleRate, 1.0);
    //delayTimeInput.setRange(0.001, 1);

    displayPage.initTitle("Phaser");
}

void PhaserController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        out[LEFT][i] = filterLeft.process(in[LEFT][i]);
        out[RIGHT][i] = filterLeft.process(in[RIGHT][i]);
    }
}

void PhaserController::update() {
    delayTimeInput.update();
    feedbackInput.update();
    dryWetMixInput.update();

    filterLeft.setDelayTime(delayTimeInput.getValue());
    filterLeft.setFeedback(feedbackInput.getValue());
}