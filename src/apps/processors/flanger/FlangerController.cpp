#include "FlangerController.h"

#define LEFT 0
#define RIGHT 1

void FlangerController::init(float sampleRate) {
    this->sampleRate = sampleRate;
    delayLeft.init(sampleRate);
    delayRight.init(sampleRate);
    //delayTimeInput.setRange(0.001, 1);

    displayPage.initTitle("Comb Filter (Flanger)");
}

void FlangerController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        out[LEFT][i] = delayLeft.process(in[LEFT][i]);
        out[RIGHT][i] = delayRight.process(in[RIGHT][i]);
    }
}

void FlangerController::setDelay(float delayTime) {
    delayLeft.setDelay(delayTime);
    delayRight.setDelay(delayTime);
}

void FlangerController::update() {
    delayTimeInput.update();
    feedbackInput.update();
    dryWetMixInput.update();

    delayLeft.setDelay(delayTimeInput.getValue());
    delayRight.setDelay(delayTimeInput.getValue());
    delayLeft.setFeedbackLevel(feedbackInput.getValue());
    delayRight.setFeedbackLevel(feedbackInput.getValue());
    delayLeft.setDryLevel(dryWetMixInput.getDryLevel());
    delayRight.setDryLevel(dryWetMixInput.getDryLevel());
    delayLeft.setWetLevel(dryWetMixInput.getWetLevel());
    delayRight.setWetLevel(dryWetMixInput.getWetLevel());
}