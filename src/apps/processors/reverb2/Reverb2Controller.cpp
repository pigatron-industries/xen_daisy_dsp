#include "Reverb2Controller.h"

#define LEFT 0
#define RIGHT 1

#define DELAY_BUFFER_SIZE 1

void Reverb2Controller::init(float sampleRate) {
    this->sampleRate = sampleRate;
    reverb.Init(sampleRate);
    displayPage.initTitle("Reverb 2", "VRB2");
}

void Reverb2Controller::update() {
    if(feedbackInput.update()) {
        reverb.SetFeedback(feedbackInput.getValue());
    }
    if(filterInput.update()) {
        reverb.SetLpFreq(filterInput.getValue());
    }
    dryWetMix.update();
}

void Reverb2Controller::process(float **in, float **out, size_t size) {
    float out1, out2, in1, in2;
    for (size_t i = 0; i < size; i++) {
        in1 = in[LEFT][i];
        in2 = in[RIGHT][i];
        reverb.Process(in1, in2, &out1, &out2);
        out[LEFT][i] = out1 * dryWetMix.getWetLevel() + in1 * dryWetMix.getDryLevel();
        out[RIGHT][i] = out2 * dryWetMix.getWetLevel() + in2 * dryWetMix.getDryLevel();
    }
}
