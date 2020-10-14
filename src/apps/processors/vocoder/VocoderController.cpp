#include "VocoderController.h"

#define LEFT 0
#define RIGHT 1

#define FIELD_VOCODER_BANDS 1

void VocoderController::init(float sampleRate) {
    vocoder.init(sampleRate);
    vocoder.initBands(55.0, 0.3333, 1); // 1/3 octave 400 cents
    vocoder.setUseCarrierOscillator(true);

    displayPage.initTitle("Vocoder");
    displayPage.initField(FIELD_VOCODER_BANDS, String(vocoder.getBandCount()), false);
}

void VocoderController::update() {
    resonanceInput.update();
    frequencyRatio.update();
    vocoder.setResonance(resonanceInput.getValue());
}

void VocoderController::updateDisplay() { 
    //vocoder.initBands(55.0, frequencyRatio.getValue(), 6); //TODO only call this when input value has changed significantly OR limit to specific frequencies
    displayPage.setText(FIELD_VOCODER_BANDS, String(vocoder.getBandCount()));
}

void VocoderController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        out[LEFT][i] = vocoder.process(in[LEFT][i], in[RIGHT][i]);
        out[RIGHT][i] = out[LEFT][i];
    }
}
