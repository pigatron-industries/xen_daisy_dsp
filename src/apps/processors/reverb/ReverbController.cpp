#include "ReverbController.h"
//#include "io/MemPool.h"

#define LEFT 0
#define RIGHT 1

#define DELAY_BUFFER_SIZE 1

void ReverbController::init(float sampleRate) {
    this->sampleRate = sampleRate;
    delayInput.setSmoothingWeight(SMOOTHING_FAST);
    reverb.init(sampleRate);
    displayPage.initTitle("Reverb", "VERB");
}

void ReverbController::update() {
    delayInput.update();
    if(dryWetMix.update()) {
        reverb.setDryLevel(dryWetMix.getDryLevel());
        reverb.setWetLevel(dryWetMix.getWetLevel());
    }
    if(feedbackInput.update()) {
        reverb.setFeedback(feedbackInput.getValue());
    }
    if(filterInput.update()) {
        if(filterInput.getLowPass()) {
            reverb.setLowPassFilterFrequency(filterInput.getFrequency());
            reverb.setLowPassFilter(true);
            reverb.setHighPassFilter(false);
        } else if (filterInput.getHighPass()) {
            reverb.setHighPassFilterFrequency(filterInput.getFrequency());
            reverb.setHighPassFilter(true);
            reverb.setLowPassFilter(false);
        } else {
            reverb.setHighPassFilter(false);
            reverb.setLowPassFilter(false);
        }
    }
}

void ReverbController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        reverb.setDelay(delayInput.getValue());
        reverb.process(in[LEFT][i] + in[RIGHT][i]);
        out[LEFT][i] = reverb.getOutput(1);
        out[RIGHT][i] = reverb.getOutput(2);
    }
}