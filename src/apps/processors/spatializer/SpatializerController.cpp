#include "SpatializerController.h"

#define LEFT 0
#define RIGHT 1

void SpatializerController::init(float sampleRate) {
    spatializer1.init(sampleRate);
    spatializer1.setDestinationPosition(0, 0.0, 0.1);
    spatializer1.setDestinationPosition(0, 0.0, -0.1);
    spatializer2.init(sampleRate);
    spatializer2.setDestinationPosition(0, 0.0, 0.1);
    spatializer2.setDestinationPosition(0, 0.0, -0.1);
    displayPage.initTitle("Spatializer");
}

void SpatializerController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        spatializer1.process(in[LEFT][i]);
        spatializer2.process(in[RIGHT][i]);
        out[LEFT][i] = spatializer1.getOutput(LEFT) + spatializer2.getOutput(LEFT);
        out[RIGHT][i] = spatializer1.getOutput(RIGHT) + spatializer2.getOutput(RIGHT);
    }
}


void SpatializerController::update() {
    if(x1Input.update() || y1Input.update()) {
        spatializer1.setSourcePosition(x1Input.getValue(), y1Input.getValue());
    }
    if(x2Input.update() || y2Input.update()) {
        spatializer2.setSourcePosition(x2Input.getValue(), y2Input.getValue());
    }
}