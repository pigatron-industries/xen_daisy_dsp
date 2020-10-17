#include "VocoderController.h"

#define LEFT 0
#define RIGHT 1

#define FIELD_VOCODER_BANDS 1
#define FIELD_VOCODER_FREQUENCYBASE 2
#define FIELD_VOCODER_PITCHINTERVAL 3

void VocoderController::init(float sampleRate) {
    vocoder.init(sampleRate);
    vocoder.initBands(110.0, 0.3333, 10); // 1/3 octave 400 cents
    vocoder.setUseCarrierOscillator(false);

    displayPage.initTitle("Vocoder");
    displayPage.initField(FIELD_VOCODER_BANDS, false);
    displayPage.initField(FIELD_VOCODER_FREQUENCYBASE, false);
    displayPage.initField(FIELD_VOCODER_PITCHINTERVAL, false);
}

void VocoderController::update() { 
    if(resonanceInput.update()) {
        vocoder.setResonance(resonanceInput.getValue());
    }
    frequencyBaseInput.update();
    pitchIntervalInput.update();
    bandsInput.update();
    if(frequencyBaseInput.isChanged() || pitchIntervalInput.isChanged() || bandsInput.isChanged()) {
        vocoder.initBands(frequencyBaseInput.getValue(), pitchIntervalInput.getValue(), int(bandsInput.getValue()));
    }
}

void VocoderController::updateDisplay() { 
    displayPage.setText(FIELD_VOCODER_BANDS, String("Bands: ") + String(vocoder.getBandCount()));
    displayPage.setText(FIELD_VOCODER_FREQUENCYBASE, String("Frequency Base: ") + String(vocoder.getFrequencyBase(), 0));
    displayPage.setText(FIELD_VOCODER_PITCHINTERVAL, String("Pitch Interval: ") + String(vocoder.getPitchInterval(), 3));
}

void VocoderController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        out[LEFT][i] = vocoder.process(in[LEFT][i], in[RIGHT][i]);
        out[RIGHT][i] = out[LEFT][i];
    }
}
