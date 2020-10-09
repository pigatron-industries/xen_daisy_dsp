#include "VowelizerController.h"

#define LEFT 0
#define RIGHT 1

void VowelizerController::init(float sampleRate) {
    vowelizer.init(sampleRate);

    displayPage.initTitle("Vowel Filter");
}

void VowelizerController::update() {
    rangeInput.update();
    vowelInput.update();
    pitchInput.update();
    resonanceInput.update();

    vowelizer.setVowelAndRange(vowelInput.getValue(), rangeInput.getValue());
    vowelizer.setPitch(pitchInput.getValue());
    vowelizer.setResonance(resonanceInput.getValue());
}

void VowelizerController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        out[LEFT][i] = vowelizer.process(in[LEFT][i]);
    }
}
