#include "GlitchAliasController.h"

#define LEFT 0
#define RIGHT 1

void GlitchAliasController::init(float sampleRate) {
    square.init(sampleRate);
    square.setWaveform(pigatron::Oscillator::WAVE_SQUARE);
    square.setAllowHighFrequency(true);
    saw.init(sampleRate);
    saw.setWaveform(pigatron::Oscillator::WAVE_SAW);
    saw.setAllowHighFrequency(true);
    
    displayPage.initTitle("Aliasing Oscillator", "ALIA");
}

void GlitchAliasController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        float sample = square.process() * mix + saw.process() * (1-mix);
        out[LEFT][i] = sample;
        out[RIGHT][i] = sample;
    }
}

void GlitchAliasController::update() {
    pitchInput.update();
    fineInput.update();
    mixInput.update();
    square.setFrequency(pitchInput.getValue() + fineInput.getValue());
    saw.setFrequency(pitchInput.getValue() + fineInput.getValue());
    mix = mixInput.getValue();
}