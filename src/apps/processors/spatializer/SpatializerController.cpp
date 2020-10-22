#include "SpatializerController.h"

#define LEFT 0
#define RIGHT 1

void SpatializerController::init(float sampleRate) {
    spatializer.init(sampleRate);
    displayPage.initTitle("Spatializer");
}

void SpatializerController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        spatializer.process(in[LEFT][i]);
        out[LEFT][i] = spatializer.getLeftOutput();
        out[RIGHT][i] = spatializer.getRightOutput();
    }
}


void SpatializerController::update() {
    if(panInput.update()) {
        spatializer.setPan(panInput.getValue());
    }
}