#include "PhaseDistortionController.h"

#define LEFT 0
#define RIGHT 1

void PhaseDistortionController::init(float sampleRate) {
    oscillator.init(sampleRate);

    displayPage.initTitle("Phase Distortion", "PHSD");
}

void PhaseDistortionController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        float output = oscillator.process();
        out[LEFT][i] = output;
        out[RIGHT][i] = output;
    }
}

void PhaseDistortionController::update() {
    if(pitchInput.update()) {
        oscillator.setFrequency(pitchInput.getValue());
    }

    if(xInput.update() || yInput.update()) {
        oscillator.getEnvelope().setPoint(1, Point(xInput.getValue(), yInput.getValue()));
    }

    if(phaseOffsetInput.update()) {
        oscillator.setPhaseOffset(phaseOffsetInput.getValue());
    }
}