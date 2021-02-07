#include "DripController.h"

#define LEFT 0
#define RIGHT 1

void DripController::init(float sampleRate) {
    drip.init(sampleRate, 5);
    displayPage.initTitle("Drip", "DRIP");
}

void DripController::update() {
    if(gateInput.update()) {
        trigger = gateInput.isTriggered();
    } else {
        trigger = false;
    }
}

void DripController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        float output = drip.process(trigger);
        out[LEFT][i] = output;
        out[RIGHT][i] = output;
    }
}
