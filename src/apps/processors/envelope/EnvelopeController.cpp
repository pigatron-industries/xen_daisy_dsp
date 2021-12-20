#include "EnvelopeController.h"

#define LEFT 0
#define RIGHT 1

void EnvelopeController::init(float sampleRate) {
    envelope.init(sampleRate, 3, 1, false);
    envelope.setPoint(0, Point(0, 0));
    envelope.setPoint(1, Point(1, 1));
    envelope.setPoint(2, Point(2, 0));

    displayPage.initTitle("Envelope", "ENV ");
}

void EnvelopeController::update() {
    if(gateInput.update()) {
        if(gateInput.isTriggeredOn()) {
            envelope.trigger();
        }
    }

    if(attackTimeInput.update()) {
        envelope.setSegmentLength(0, attackTimeInput.getValue());
    }
    if(decayTimeInput.update()) {
        envelope.setSegmentLength(1, decayTimeInput.getValue());
    }
}

void EnvelopeController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        float gain = envelope.process();
        out[LEFT][i] = in[LEFT][i] * gain;
        out[RIGHT][i] = in[RIGHT][i] * gain;
    }
}