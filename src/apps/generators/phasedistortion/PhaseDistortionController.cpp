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

    wavetableSine1.init(Hardware::hw.permPool);
    WaveTableFactory::addSine(&wavetableSine1, 0.5);
    wavetableSine2.init(Hardware::hw.permPool);
    WaveTableFactory::addSine(&wavetableSine2, 0.5, 2);
    wavetableSine3.init(Hardware::hw.permPool);
    WaveTableFactory::addSine(&wavetableSine3, 0.5, 3);
    wavetableSine4.init(Hardware::hw.permPool);
    WaveTableFactory::addSine(&wavetableSine4, 0.5, 4);
    wavetableSine5.init(Hardware::hw.permPool);
    WaveTableFactory::addSine(&wavetableSine5, 0.5, 5);

    wavetableRamp1.init(Hardware::hw.permPool);
    WaveTableFactory::addRamp(&wavetableRamp1, 0.5);
    wavetableRamp2.init(Hardware::hw.permPool);
    WaveTableFactory::addRamp(&wavetableRamp2, 0.5, 2);
    wavetableRamp3.init(Hardware::hw.permPool);
    WaveTableFactory::addRamp(&wavetableRamp3, 0.5, 3);
    wavetableRamp4.init(Hardware::hw.permPool);
    WaveTableFactory::addRamp(&wavetableRamp4, 0.5, 4);
    wavetableRamp5.init(Hardware::hw.permPool);
    WaveTableFactory::addRamp(&wavetableRamp5, 0.5, 5);

    wavetableSquare1.init(Hardware::hw.permPool);
    WaveTableFactory::addSquare(&wavetableSquare1, 0.5);
    wavetableSquare2.init(Hardware::hw.permPool);
    WaveTableFactory::addSquare(&wavetableSquare2, 0.5, 2);
    wavetableSquare3.init(Hardware::hw.permPool);
    WaveTableFactory::addSquare(&wavetableSquare3, 0.5, 3);
    wavetableSquare4.init(Hardware::hw.permPool);
    WaveTableFactory::addSquare(&wavetableSquare4, 0.5, 4);
    wavetableSquare5.init(Hardware::hw.permPool);
    WaveTableFactory::addSquare(&wavetableSquare5, 0.5, 5);

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
        //oscillator.setPhaseOffset(phaseOffsetInput.getValue());
        interpolator.select(waveInput.getValue());
    }

    if(harmonicsInput.update()) {
        sineInterpolator.select(harmonicsInput.getValue());
        rampInterpolator.select(harmonicsInput.getValue());
        squareInterpolator.select(harmonicsInput.getValue());
    }
}