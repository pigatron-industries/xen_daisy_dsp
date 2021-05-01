#include "OscillatorCluster.h"
#include "modules/wavetable/WaveTableGenerator.h"

#define TABLE_SIZE 256

void OscillatorCluster::init(float sampleRate) {
    sine.init(sampleRate, TABLE_SIZE, 1, SDRAM_PERM);
    WaveTableGenerator::addSine(sine, 0.5);
    baseFrequency = 220;

    for(int i = 0; i < MAX_OSCILLATORS; i++) {
        oscillators[i].init(sampleRate, TABLE_SIZE);
        oscillators[i].setWaveTable(0, &sine);
        frequencyMultipliers[i] = 1;
    }
}

void OscillatorCluster::setInterval(float interval) {
    float mult = 1;
    for(int i = 0; i < MAX_OSCILLATORS; i++) {
        frequencyMultipliers[i] = mult;
        mult += interval;
    }
    updateFrequencies();
}

void OscillatorCluster::setBaseFrequency(float frequency) {
    this->baseFrequency = baseFrequency;
    updateFrequencies();
}

void OscillatorCluster::updateFrequencies() {
    for(int i = 0; i < MAX_OSCILLATORS; i++) {
        oscillators[i].setFrequency(baseFrequency * frequencyMultipliers[i]);
    }
}