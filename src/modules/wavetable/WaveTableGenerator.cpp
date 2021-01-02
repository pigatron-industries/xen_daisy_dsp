#include "WaveTableGenerator.h"

#include <math.h>
#include "../../util/util.h"

bool WaveTableGenerator::addSine(WaveTable& wavetable, float amplitude, int mult) {
    float nyquist = wavetable.getSampleRate() * 0.5;
    size_t size = wavetable.getSize();
    float* tempBuffer = wavetable.getTempBuffer();
    bool added = false;
    float phaseIncrement = (1 / float(size)) * M_PI*2 * mult;

    for(int tableIndex = 0; tableIndex < wavetable.getTableCount(); tableIndex++) {
        float maxFrequency = wavetable.getTableFrequency(tableIndex) * mult;
        if(maxFrequency <= nyquist) {
            added = true;
            if(tableIndex == 0) {
                float phase = 0;
                for(int i = 0; i < size; i++) {
                    tempBuffer[i] = sinf(phase) * amplitude;
                    phase += phaseIncrement;
                }
            } 
            wavetable.addTempBufferToTable(tableIndex);
        }
    }

    return added;
}

void WaveTableGenerator::addHarmonics(WaveTable& wavetable, RollOffFunction* rolloff, float amplitude, int mult) {
    int harmonic = 1;
    bool added = true;
    while(added) {
        float harmonicAmplitude = rolloff->rolloff(harmonic) * amplitude;
        if(harmonicAmplitude > 0) {
            int harmonicMult = harmonic * mult;
            added = addSine(wavetable, harmonicAmplitude, harmonicMult);
        }
        harmonic++;
    }
}

void WaveTableGenerator::addSquare(WaveTable& wavetable, float amplitude, int mult) {
    SquareRollOffFunction rolloff = SquareRollOffFunction();
    addHarmonics(wavetable, &rolloff, amplitude, mult);
}

void WaveTableGenerator::addTriangle(WaveTable& wavetable, float amplitude, int mult) {
    TriangleRollOffFunction rolloff = TriangleRollOffFunction();
    addHarmonics(wavetable, &rolloff, amplitude, mult);
}

void WaveTableGenerator::addRamp(WaveTable& wavetable, float amplitude, int mult) {
    RampRollOffFunction rolloff = RampRollOffFunction();
    addHarmonics(wavetable, &rolloff, amplitude, mult);
}

void WaveTableGenerator::addPulse(WaveTable& wavetable, float amplitude, int mult) {
    PulseRollOffFunction rolloff = PulseRollOffFunction();
    addHarmonics(wavetable, &rolloff, amplitude, mult);
}

void WaveTableGenerator::pulse(WaveTable& wavetable, float pulseWidth, float amplitude, int mult) {
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
