#include "PhaseDistortionController.h"
#include "modules/wavetable/WaveTableGenerator.h"

#define LEFT 0
#define RIGHT 1

#define TABLE_SIZE 256

#if defined(XEN_CV6)
    #define POINT_COUNT 1
#else
    #define POINT_COUNT 4
#endif

void PhaseDistortionController::init(float sampleRate) {

    for(int i = 0; i < 5; i++) {
        interpolator[0][i].init(Hardware::hw.permPool);
        WaveTableFactory::addSine(&interpolator[0][i], 0.5, i+1);
    }
    for(int i = 0; i < 5; i++) {
        interpolator[1][i].init(Hardware::hw.permPool);
        WaveTableFactory::addRamp(&interpolator[1][i], 0.5, i+1);
    }
    for(int i = 0; i < 5; i++) {
        interpolator[2][i].init(Hardware::hw.permPool);
        WaveTableFactory::addSquare(&interpolator[2][i], 0.5, i+1);
    }

    oscillator.init(sampleRate);

    displayPage.initTitle("Phase Distortion", "PHSD");
}

void PhaseDistortionController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        float output = oscillator.process();
        out[LEFT][i] = output;
        out[RIGHT][i] = output;
    }
}

void PhaseDistortionController::update() {
    if(pitchInput.update()) {
        oscillator.setFrequency(pitchInput.getValue());
    }

    if(x1Input.update() || y1Input.update()) {
        distortionFunction.setMidPoint(x1Input.getValue(), y1Input.getValue());
    }

    if(waveInput.update()) {
        interpolator.setInterpolationY(waveInput.getValue());
    }

    if(harmonicsInput.update()) {
        interpolator.setInterpolationX(harmonicsInput.getValue());
    }
}