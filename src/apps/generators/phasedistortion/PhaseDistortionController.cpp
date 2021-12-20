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
    wavetable1.init(sampleRate, TABLE_SIZE, 10, Hardware::hw.permPool);
    WaveTableGenerator::addSine(wavetable1, 0.5);

    wavetable2.init(sampleRate, TABLE_SIZE, 10, Hardware::hw.permPool);
    WaveTableGenerator::addSine(wavetable2, 0.5, 2);

    wavetable3.init(sampleRate, TABLE_SIZE, 10, Hardware::hw.permPool);
    WaveTableGenerator::addSine(wavetable3, 0.5, 3);

    wavetable4.init(sampleRate, TABLE_SIZE, 10, Hardware::hw.permPool);
    WaveTableGenerator::addSine(wavetable4, 0.5, 4);

    wavetable5.init(sampleRate, TABLE_SIZE, 10, Hardware::hw.permPool);
    WaveTableGenerator::addSine(wavetable5, 0.5, 5);

    oscillator.init(sampleRate, TABLE_SIZE, POINT_COUNT);
    oscillator.getOscillator().setWaveTable(0, wavetable1);
    oscillator.getOscillator().setWaveTable(1, wavetable2);
    oscillator.getOscillator().setWaveTable(2, wavetable3);
    oscillator.getOscillator().setWaveTable(3, wavetable4);
    oscillator.getOscillator().setWaveTable(4, wavetable5);
    oscillator.getEnvelope().setPoint(0, Point(0, 0));
    oscillator.getEnvelope().setPoint(POINT_COUNT+1, Point(1, 1));

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
        Serial.println("x");
        Serial.println(x1Input.getValue());
        Serial.println("y");
        Serial.println(y1Input.getValue());
        oscillator.getEnvelope().setPoint(1, Point(x1Input.getValue(), y1Input.getValue()));
    }

    // if(phaseOffsetInput.update()) {
    //     oscillator.setPhaseOffset(phaseOffsetInput.getValue());
    // }

    if(harmonicsInput.update()) {
        oscillator.getOscillator().setInterpolation(harmonicsInput.getValue());
    }
}