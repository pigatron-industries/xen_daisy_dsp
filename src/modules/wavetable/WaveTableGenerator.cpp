#include "WaveTableGenerator.h"

#include <math.h>
#include "../../util/util.h"

void WaveTableGenerator::sine(WaveTable& wavetable, float amplitude, int mult) {
    size_t size = wavetable.getSize();
    for(int i = 0; i < size; i++) {
        float phase = (float(i) / float(size)) * M_PI*2 * mult;
        wavetable.addTableSample(i, sinf(phase) * amplitude);
    }
}

bool WaveTableGenerator::blSine(WaveTable& wavetable, float amplitude, int mult) {
    float nyquist = wavetable.getSampleRate() * 0.5;
    size_t size = wavetable.getSize();
    bool added = false;

    for(int tableIndex = 0; tableIndex < wavetable.getTableCount(); tableIndex++) {
        float maxFrequency = wavetable.getTableFrequency(tableIndex) * mult;
        if(maxFrequency < nyquist) {
            added = true;
            for(int i = 0; i < size; i++) {
                float phase = (float(i) / float(size)) * M_PI*2 * mult;
                float sample = sinf(phase) * amplitude;
                wavetable.addTableSample(tableIndex, i, sample);
            }
        }
    }

    return added;
}

void WaveTableGenerator::square(WaveTable& wavetable, float pulseWidth, float amplitude, int mult) {
    size_t size = wavetable.getSize();
    for(int i = 0; i < size; i++) {
        float phase = (float(i) / float(size)) * mult;
        int intPhase = static_cast<int>(phase);
        float fracPhase = phase - static_cast<float>(intPhase);
        wavetable.addTableSample(i, fracPhase < pulseWidth ? amplitude : -amplitude);
    }
}

void WaveTableGenerator::blSquare(WaveTable& wavetable, float amplitude, int mult) {
    int harmonic = 1;
    bool added = true;

    while(added) {
        float harmonicAmplitude = amplitude/float(harmonic);
        int harmonicMult = harmonic * mult;
        added = blSine(wavetable, harmonicAmplitude, harmonicMult);
        harmonic += 2;
    }
}

void WaveTableGenerator::triangle(WaveTable& wavetable, float amplitude, int mult) {
    size_t size = wavetable.getSize();
    for(int i = 0; i < size; i++) {
        float phase = (float(i) / float(size)) * mult;
        float t = -1.0f + (2.0f * fmodf(phase, 1.0));
        wavetable.addTableSample(i, amplitude * 2.0f * (fabsf(t) - 0.5f));
    }
}

void WaveTableGenerator::ramp(WaveTable& wavetable, float amplitude, int mult) {
    size_t size = wavetable.getSize();
    for(int i = 0; i < size; i++) {
        float phase = (float(i) / float(size)) * mult;
        wavetable.addTableSample(i, (((fmodf(phase, 1.0) * 2.0f)) - 1.0f) * amplitude);
    }
}
