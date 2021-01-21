#include "GlottisController.h"

#define LEFT 0
#define RIGHT 1


void GlottisController::init(float sampleRate) {
    whiteNoise.Init();
    aspirateFilter.init(sampleRate);
    //aspirateFilter.setGain(1.0);
    aspirateFilter.setQ(0.5);
    aspirateFilter.setFrequency(500);
    glottis.init(sampleRate);
    vibrato.init(sampleRate);

    displayPage.initTitle("Glottis", "GLOT");
}

void GlottisController::update() {
    if(pitchInput.update()) {
        vibrato.setTargetValue(pitchInput.getValue());
    }
    if(tensenessInput.update()) {
        glottis.setTenseness(tensenessInput.getValue());
    }
    if(vibratoAmountInput.update()) {
        vibrato.setVibratoAmount(vibratoAmountInput.getValue());
    }
    if(noiseAmountInput.update()) {
        vibrato.setNoiseAmount(noiseAmountInput.getValue());
    }
}

void GlottisController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {

        //Noise
        float noise = whiteNoise.Process();
        float aspirate = aspirateFilter.process(noise);

        //Glottis
        glottis.setFrequency(vibrato.process());
        float glot = glottis.process(aspirate);
        
        out[LEFT][i] = glot;
        out[RIGHT][i] = glot;
    }

    //vibrato.update();
}