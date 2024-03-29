#include "WaveTablePresets.h"
#include "WaveTableGenerator.h"
#include "io/Hardware.h"

using namespace deprecated;

WaveTablePresets WaveTablePresets::presets = WaveTablePresets();

void WaveTablePresets::init(float sampleRate) {
    this->sampleRate = sampleRate;
}

WaveTable& WaveTablePresets::getWaveTable(WaveformPreset waveformPreset) {
    switch (waveformPreset) {
        case WAVE_SINE:
            if(!sine.isInited()) {
                initSine();
            } 
            return sine;
        case WAVE_TRIANGLE:
            if(!triangle.isInited()) {
                initTriangle();
            } 
            return sine;
        case WAVE_RAMP:
            if(!ramp.isInited()) {
                initRamp();
            } 
            return ramp;
        case WAVE_SQUARE:
            if(!square.isInited()) {
                initSquare();
            } 
            return square;
        case WAVE_IMPULSE:
            if(!triangle.isInited()) {
                initTriangle();
            } 
            return ramp;
        case WAVE_VIOLIN:
            if(!violin.isInited()) {
                initViolin();
            } 
            return violin;
    }
}

void WaveTablePresets::initSine() {
    sine.init(sampleRate, TABLE_SIZE, 10, Hardware::hw.permPool);
    WaveTableGenerator::addSine(sine, 0.5);
}

void WaveTablePresets::initTriangle() {
    triangle.init(sampleRate, TABLE_SIZE, 10, Hardware::hw.permPool);
    WaveTableGenerator::addTriangle(triangle, 0.5);
}

void WaveTablePresets::initRamp() {
    ramp.init(sampleRate, TABLE_SIZE, 10, Hardware::hw.permPool);
    WaveTableGenerator::addRamp(ramp, 0.5);
}

void WaveTablePresets::initSquare() {
    square.init(sampleRate, TABLE_SIZE, 10, Hardware::hw.permPool);
    WaveTableGenerator::addSquare(square, 0.5);
}

void WaveTablePresets::initImpulse() {
    impulse.init(sampleRate, TABLE_SIZE, 10, Hardware::hw.permPool);
    WaveTableGenerator::addImpulse(impulse, 0.5);
}

void WaveTablePresets::initViolin() {
    violin.init(sampleRate, TABLE_SIZE, 10, Hardware::hw.permPool);
    WaveTableGenerator::addViolin(violin, 0.5);
}
