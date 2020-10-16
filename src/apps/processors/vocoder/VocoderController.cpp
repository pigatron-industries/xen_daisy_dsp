#include "VocoderController.h"

#define LEFT 0
#define RIGHT 1

#define FIELD_VOCODER_BANDS 1
#define FIELD_VOCODER_FREQUENCYBASE 2
#define FIELD_VOCODER_PITCHINTERVAL 3

void VocoderController::init(float sampleRate) {
    vocoder.init(sampleRate);
    vocoder.initBands(110.0, 0.3333, bandCount); // 1/3 octave 400 cents
    vocoder.setUseCarrierOscillator(false);

    displayPage.initTitle("Vocoder");
    displayPage.initField(FIELD_VOCODER_BANDS, false);
    displayPage.initField(FIELD_VOCODER_FREQUENCYBASE, false);
    displayPage.initField(FIELD_VOCODER_PITCHINTERVAL, false);
}

void VocoderController::update() { 
    resonanceInput.update();
    frequencyBaseInput.update();
    pitchIntervalInput.update();
    bandsInput.update();
    vocoder.setResonance(resonanceInput.getValue());
    vocoder.initBands(frequencyBaseInput.getValue(), pitchIntervalInput.getValue(), int(bandsInput.getValue())); //TODO only call if there has been a change
}

void VocoderController::updateDisplay() { 
    //TODO only update fields when there is a change
    displayPage.setText(FIELD_VOCODER_BANDS, String("Bands: ") + String(vocoder.getBandCount()));
    displayPage.setText(FIELD_VOCODER_FREQUENCYBASE, String("Frequency Base: ") + String(vocoder.getFrequencyBase()));
    displayPage.setText(FIELD_VOCODER_PITCHINTERVAL, String("Pitch Interval: ") + String(vocoder.getPitchInterval(), 4));
}

void VocoderController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        out[LEFT][i] = vocoder.process(in[LEFT][i], in[RIGHT][i]);
        out[RIGHT][i] = out[LEFT][i];
    }
}
