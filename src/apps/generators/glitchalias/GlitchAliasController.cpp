#include "GlitchAliasController.h"

#define LEFT 0
#define RIGHT 1

void GlitchAliasController::init(float sampleRate) {
    square.Init(sampleRate);
    square.SetWaveform(Oscillator::WAVE_SQUARE);
    saw.Init(sampleRate);
    saw.SetWaveform(Oscillator::WAVE_SAW);
    
    displayPage.initTitle("Aliasing Oscillator");
}

void GlitchAliasController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        float sample = square.Process() * mix + saw.Process() * (1-mix);
        out[LEFT][i] = sample;
        out[RIGHT][i] = sample;
    }
}

void GlitchAliasController::update() {
    pitchInput.update();
    fineInput.update();
    mixInput.update();
    square.SetFreq(pitchInput.getValue() + fineInput.getValue());
    saw.SetFreq(pitchInput.getValue() + fineInput.getValue());
    mix = mixInput.getValue();
}