#include "DelayController.h"

#define LEFT 0
#define RIGHT 1

#define MAX_DELAY 60

void DelayController::init(float sampleRate) {
    this->sampleRate = sampleRate;
    delayLeft.init(sampleRate, MAX_DELAY);
    delayRight.init(sampleRate, MAX_DELAY);

    displayPage.initTitle("Delay", "DLAY");
}

void DelayController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        delayLeft.setDelay(delayLeftSlewLimiter.update());
        delayRight.setDelay(delayRightSlewLimiter.update());
        out[LEFT][i] = delayLeft.process(in[LEFT][i]);
        out[RIGHT][i] = delayRight.process(in[RIGHT][i]);
    }
}

void DelayController::setDelay(float delayTime) {
    delayLeft.setDelay(delayTime);
    delayRight.setDelay(delayTime);
}

void DelayController::update() {
    if(delayTimeLeftInput.update()) {
        delayLeftSlewLimiter.setTargetValue(delayTimeLeftInput.getValue());
    }
    if(delayTimeRightInput.update()) {
        delayRightSlewLimiter.setTargetValue(delayTimeRightInput.getValue());
    }

    if(feedbackInput.update()) {
        delayLeft.setFeedbackLevel(feedbackInput.getValue());
        delayRight.setFeedbackLevel(feedbackInput.getValue());
    }
    if(dryWetMixInput.update()) {
        delayLeft.setDryLevel(dryWetMixInput.getDryLevel());
        delayRight.setDryLevel(dryWetMixInput.getDryLevel());
        delayLeft.setWetLevel(dryWetMixInput.getWetLevel());
        delayRight.setWetLevel(dryWetMixInput.getWetLevel());
    }
}