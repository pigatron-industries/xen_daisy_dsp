#include "VowelizerController.h"

#define LEFT 0
#define RIGHT 1

VowelizerController::VowelizerController():
    rangeInput(A0, -5, 5, 0, 5),
    vowelInput(A1, -5, 5, 0, 5),
    pitchInput(A2, -5, 5, 1, 2) {
}

void VowelizerController::init(float sampleRate) {
    vowelizer.init(sampleRate);
}

void VowelizerController::update() {
    rangeInput.update();
    vowelInput.update();
    pitchInput.update();
}

void VowelizerController::process(float **in, float **out, size_t size) {
    vowelizer.setVowelAndRange(vowelInput.getVirtualValue(), rangeInput.getVirtualValue());
    vowelizer.setPitch(pitchInput.getVirtualValue());

    for (size_t i = 0; i < size; i++) {
        out[LEFT][i] = vowelizer.process(in[LEFT][i]);
    }
}

