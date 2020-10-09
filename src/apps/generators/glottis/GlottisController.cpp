#include "GlottisController.h"

#define LEFT 0
#define RIGHT 1


void GlottisController::init(float sampleRate) {
    whiteNoise.Init();
    aspirateFilter.init(sampleRate);
    aspirateFilter.setGain(1.0);
    aspirateFilter.setQ(0.5);
    aspirateFilter.setFrequency(500);
    glottis.init(sampleRate);

    displayPage.initTitle("Glottis");
}

void GlottisController::update() {
    pitchInput.update();
    tensenessInput.update();

    glottis.setFrequency(pitchInput.getFrequency());
    glottis.setTenseness(tensenessInput.getValue());
}

void GlottisController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {

        //Noise
        float noise = whiteNoise.Process();
        float aspirate = aspirateFilter.process(noise);

        //Glottis
        float lambda1 = (float)i / (float)size;
        float glot = glottis.process(lambda1, aspirate);
        
        out[LEFT][i] = glot;
        out[RIGHT][i] = glot;
    }

    glottis.finishBlock();
}