#include "FrequencyCounterController.h"

#define LEFT 0
#define RIGHT 1

#define FIELD_FREQ 1


void FrequencyCounterController::init(float sampleRate) {
    displayPage.initTitle("Frequency Counter", "FREQ");
    displayPage.initField(FIELD_FREQ, false);
    counter.init(sampleRate);
}

void FrequencyCounterController::update() {
    //pitchOutput.setFrequency(autocorrelationAnalyser.getFrequency());
}

void FrequencyCounterController::updateDisplay() {
    displayPage.setText(FIELD_FREQ, String(counter.getFrequency(), 2));
}

void FrequencyCounterController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        counter.process(in[LEFT][i]);
        out[LEFT][i] = in[LEFT][i];
        out[RIGHT][i] = in[RIGHT][i];
    }
}
