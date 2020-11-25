#include "SpatializerController.h"

#define LEFT 0
#define RIGHT 1

void SpatializerController::init(float sampleRate) {
    spatializer.init(sampleRate);
    spatializer.setDestinationPosition(0, 0.0, 0.1);
    spatializer.setDestinationPosition(0, 0.0, -0.1);
    displayPage.initTitle("Spatializer");
}

void SpatializerController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        spatializer.process(in[LEFT][i]);
        out[LEFT][i] = spatializer.getOutput(LEFT);
        out[RIGHT][i] = spatializer.getOutput(RIGHT);
    }
}


void SpatializerController::update() {
    if(xInput.update() || yInput.update()) {
        spatializer.setSourcePosition(xInput.getValue(), yInput.getValue());
    }
}