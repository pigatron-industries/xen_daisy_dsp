#include "ReverbController.h"
#include "../../../io/MemPool.h"

#define LEFT 0
#define RIGHT 1

#define DELAY_BUFFER_SIZE 1

void ReverbController::init(float sampleRate) {
    this->sampleRate = sampleRate;
    reverbLeft.init(sampleRate);
    reverbRight.init(sampleRate);
    displayPage.initTitle("Reverb");
}

void ReverbController::update() {
    if(dryWetMix.update()) {
        reverbLeft.setDryLevel(dryWetMix.getDryLevel());
        reverbLeft.setWetLevel(dryWetMix.getWetLevel());
    }
    if(feedbackInput.update()) {
        reverbLeft.setFeedback(feedbackInput.getValue());
    }
    if(filterInput.update()) {
        if(filterInput.getLowPass()) {
            // Serial.println("LowPass");
            // Serial.println(filterInput.getFrequency());
            reverbLeft.setLowPassFilterFrequency(filterInput.getFrequency());
            reverbLeft.setLowPassFilter(true);
            reverbLeft.setHighPassFilter(false);
        } else if (filterInput.getHighPass()) {
            // Serial.println("HighPass");
            // Serial.println(filterInput.getFrequency());
            reverbLeft.setHighPassFilterFrequency(filterInput.getFrequency());
            reverbLeft.setHighPassFilter(true);
            reverbLeft.setLowPassFilter(false);
        } else {
            reverbLeft.setHighPassFilter(false);
            reverbLeft.setLowPassFilter(false);
        }
    }
    if(delayInput.update()) {
        reverbLeft.setDelay(delayInput.getValue());
    }
}

void ReverbController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        out[LEFT][i] = reverbLeft.process(in[LEFT][i]);
        out[RIGHT][i] = out[LEFT][i];
    } 
}