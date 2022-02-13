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

    distortionFunction.segment(0).setLength(0.5);
    distortionFunction.segment(0).setStartValue(0);
    distortionFunction.segment(0).setEndValue(0.5);
    
    distortionFunction.segment(1).setLength(0.5);
    distortionFunction.segment(1).setStartValue(0.5);
    distortionFunction.segment(1).setEndValue(1);

    wavetable1.init(Hardware::hw.permPool);
    WaveTableFactory::addSine(&wavetable1, 0.5);

    wavetable2.init(Hardware::hw.permPool);
    WaveTableFactory::addSine(&wavetable2, 0.5);

    wavetable3.init(Hardware::hw.permPool);
    WaveTableFactory::addSine(&wavetable3, 0.5);

    wavetable4.init(Hardware::hw.permPool);
    WaveTableFactory::addSine(&wavetable4, 0.5);

    wavetable5.init(Hardware::hw.permPool);
    WaveTableFactory::addSine(&wavetable5, 0.5);

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
        // Serial.println("x");
        // Serial.println(x1Input.getValue());
        // Serial.println("y");
        // Serial.println(y1Input.getValue());

        distortionFunction.segment(0).setEndValue(x1Input.getValue());
        distortionFunction.segment(1).setStartValue(x1Input.getValue());
        
        distortionFunction.segment(0).setLength(y1Input.getValue());
        distortionFunction.segment(1).setLength(1.0-y1Input.getValue());
    }

    // if(phaseOffsetInput.update()) {
    //     oscillator.setPhaseOffset(phaseOffsetInput.getValue());
    // }

    if(harmonicsInput.update()) {
        //oscillator.getOscillator().setInterpolation(harmonicsInput.getValue());
    }
}