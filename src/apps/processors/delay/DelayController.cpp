#include "DelayController.h"

#define LEFT 0
#define RIGHT 1

#define MAX_DELAY 60

void DelayController::init(float sampleRate) {
    this->sampleRate = sampleRate;
    delayTimeInput.setSmoothingWeight(SMOOTHING_FAST);
    delayLeft.init(sampleRate, MAX_DELAY);
    delayRight.init(sampleRate, MAX_DELAY);

    displayPage.initTitle("Delay");
}

void DelayController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        float delayTime = delayTimeInput.getValue();
        delayLeft.setDelay(delayTime);
        delayRight.setDelay(delayTime);
        out[LEFT][i] = delayLeft.process(in[LEFT][i]);
        out[RIGHT][i] = delayRight.process(in[RIGHT][i]);
    }
}

void DelayController::setDelay(float delayTime) {
    delayLeft.setDelay(delayTime);
    delayRight.setDelay(delayTime);
}

void DelayController::update() {
    delayTimeInput.update();
    feedbackInput.update();
    dryWetMixInput.update();

    // delayLeft.setDelay(delayTimeInput.getValue());
    // delayRight.setDelay(delayTimeInput.getValue());
    delayLeft.setFeedbackLevel(feedbackInput.getValue());
    delayRight.setFeedbackLevel(feedbackInput.getValue());
    delayLeft.setDryLevel(dryWetMixInput.getDryLevel());
    delayRight.setDryLevel(dryWetMixInput.getDryLevel());
    delayLeft.setWetLevel(dryWetMixInput.getWetLevel());
    delayRight.setWetLevel(dryWetMixInput.getWetLevel());
}