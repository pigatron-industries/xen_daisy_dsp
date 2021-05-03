#include "OscillatorBank.h"
#include "modules/wavetable/WaveTableGenerator.h"

#define TABLE_SIZE 256

using namespace pigatron;

void OscillatorBank::init(float sampleRate, WaveTable& wavetable, int bandCount, FrequencyBank::PivotPoint pivotPoint, float frequency) {
    init(sampleRate, wavetable, 1, bandCount, pivotPoint, frequency);
}

void OscillatorBank::init(float sampleRate, WaveTable& wavetable, int bankCount, int bandCount, FrequencyBank::PivotPoint pivotPoint, float frequency) {
    frequencyBank.init(bankCount, bandCount, pivotPoint, frequency);
    normalizer.init(4096);
    for(int i = 0; i < MAX_OSCILLATORS; i++) {
        oscillators[i].init(sampleRate, wavetable.getSize());
        oscillators[i].setWaveTable(0, wavetable);
    }
    updateFrequencies();
}

float OscillatorBank::process() {
    float out = 0;
    for(int i = 0; i < frequencyBank.getBandCount(); i++) {
        out += oscillators[i].process();
    }
    return normalizer.process(out);
}

void OscillatorBank::updateFrequencies() {
    for(int i = 0; i < frequencyBank.getBandCount(); i++) {
        oscillators[i].setFrequency(frequencyBank.getFrequency(i));
    }
}
