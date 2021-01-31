#include "PhaseDistortionController.h"

#define LEFT 0
#define RIGHT 1

void PhaseDistortionController::init(float sampleRate) {
    phaseDistortion.init(sampleRate, &powerFunction);

    displayPage.initTitle("Phase Distortion", "PHSD");
}

void PhaseDistortionController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        float output = phaseDistortion.process();
        out[LEFT][i] = output;
        out[RIGHT][i] = output;
    }
}

void PhaseDistortionController::update() {
    if(pitchInput.update()) {
        phaseDistortion.setFrequency(pitchInput.getValue());
    }

    if(powerInput.update()) {
        powerFunction.setPower(powerInput.getValue());
    }

    if(phaseOffsetInput.update()) {
        phaseDistortion.setPhaseOffset(phaseOffsetInput.getValue());
    }
}