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

void WaveTableGenerator::square(WaveTable& wavetable, float pulseWidth, float amplitude, int mult) {
    size_t size = wavetable.getSize();
    for(int i = 0; i < size; i++) {
        float phase = (float(i) / float(size)) * mult;
        int intPhase = static_cast<int>(phase);
        float fracPhase = phase - static_cast<float>(intPhase);
        wavetable.addTableSample(i, fracPhase < pulseWidth ? amplitude : -amplitude);
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
