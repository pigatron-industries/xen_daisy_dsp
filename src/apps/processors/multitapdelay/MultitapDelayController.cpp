#include "MultitapDelayController.h"

#define LEFT 0
#define RIGHT 1

#define DELAY_BUFFER_SIZE 1

void MultitapDelayController::init(float sampleRate) {
    this->sampleRate = sampleRate;

    delayLeft.init(sampleRate, 10);
    delayLeft.setTapCount(5);

    delayRight.init(sampleRate, 10);
    delayRight.setTapCount(5);

    displayPage.initTitle("Multitap Delay", "MDLY");
}

void MultitapDelayController::update() {
    float delayTimeLeft = 0.0;
    float delayTimeRight = 0.0;
    for(int i = 0; i < 5; i++) {
        delayInputs[i*2].update();
        delayTimeLeft += delayInputs[i*2].getValue();
        delayLeft.setTap(i, delayTimeLeft, 0.2);

        delayInputs[(i*2)+1].update();
        delayTimeRight += delayInputs[(i*2)+1].getValue();
        delayRight.setTap(i, delayTimeRight, 0.2);
    }
}

void MultitapDelayController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        out[LEFT][i] = delayLeft.process(in[LEFT][i]);
        out[RIGHT][i] = delayRight.process(in[LEFT][i]);
    }
}