#include "WaveTableGenerator.h"

#include <math.h>
#include "util/mathutil.h"

bool WaveTableGenerator::addSine(deprecated::WaveTable& wavetable, float amplitude, int mult, float phaseShift) {
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
                float phase = phaseShift;
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

void WaveTableGenerator::addHarmonics(deprecated::WaveTable& wavetable, RollOffFunction* rolloff, float amplitude, int mult) {
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

void WaveTableGenerator::addSquare(deprecated::WaveTable& wavetable, float amplitude, int mult) {
    SquareRollOffFunction rolloff = SquareRollOffFunction();
    addHarmonics(wavetable, &rolloff, amplitude, mult);
}

void WaveTableGenerator::addTriangle(deprecated::WaveTable& wavetable, float amplitude, int mult) {
    TriangleRollOffFunction rolloff = TriangleRollOffFunction();
    addHarmonics(wavetable, &rolloff, amplitude, mult);
}

void WaveTableGenerator::addRamp(deprecated::WaveTable& wavetable, float amplitude, int mult) {
    RampRollOffFunction rolloff = RampRollOffFunction();
    addHarmonics(wavetable, &rolloff, amplitude, mult);
}

void WaveTableGenerator::addPulse(deprecated::WaveTable& wavetable, float amplitude, int mult) {
    PulseRollOffFunction rolloff = PulseRollOffFunction();
    addHarmonics(wavetable, &rolloff, amplitude, mult);
}

void WaveTableGenerator::addImpulse(deprecated::WaveTable& wavetable, float amplitude, int mult) {
    float amp = amplitude * -0.18;
    addSine(wavetable, amp *  1.0, mult * 1,  0);
    addSine(wavetable, amp * -0.9, mult * 2,  M_PI*0.5);
    addSine(wavetable, amp * -0.8, mult * 3,  0);
    addSine(wavetable, amp *  0.7, mult * 4,  M_PI*0.5);
    addSine(wavetable, amp *  0.6, mult * 5,  0);
    addSine(wavetable, amp * -0.5, mult * 6,  M_PI*0.5);
    addSine(wavetable, amp * -0.4, mult * 7,  0);
    addSine(wavetable, amp *  0.3, mult * 8,  M_PI*0.5);
    addSine(wavetable, amp *  0.2, mult * 9,  0);
    addSine(wavetable, amp * -0.1, mult * 10, M_PI*0.5);
}

void WaveTableGenerator::addViolin(deprecated::WaveTable& wavetable, float amplitude, int mult) {
    float amp = amplitude * 0.490;
    addSine(wavetable, amp * 0.995, mult * 1,  0);
    addSine(wavetable, amp * 0.940, mult * 2,  M_PI*0.5);
    addSine(wavetable, amp * 0.425, mult * 3,  0);
    addSine(wavetable, amp * 0.480, mult * 4,  M_PI*0.5);
    addSine(wavetable, amp * 0.365, mult * 6,  M_PI*0.5);
    addSine(wavetable, amp * 0.040, mult * 7,  0);
    addSine(wavetable, amp * 0.085, mult * 8,  M_PI*0.5);
    addSine(wavetable, amp * 0.090, mult * 10, M_PI*0.5);
}

void WaveTableGenerator::pulse(deprecated::WaveTable& wavetable, float pulseWidth, float amplitude, int mult) {
    size_t size = wavetable.getSize();
    for(int i = 0; i < size; i++) {
        float phase = (float(i) / float(size)) * mult;
        int intPhase = static_cast<int>(phase);
        float fracPhase = phase - static_cast<float>(intPhase);
        wavetable.addTableSample(i, fracPhase < pulseWidth ? amplitude : -amplitude);
    }
}

void WaveTableGenerator::triangle(deprecated::WaveTable& wavetable, float amplitude, int mult) {
    size_t size = wavetable.getSize();
    for(int i = 0; i < size; i++) {
        float phase = (float(i) / float(size)) * mult;
        float t = -1.0f + (2.0f * fmodf(phase, 1.0));
        wavetable.addTableSample(i, amplitude * 2.0f * (fabsf(t) - 0.5f));
    }
}

void WaveTableGenerator::ramp(deprecated::WaveTable& wavetable, float amplitude, int mult) {
    size_t size = wavetable.getSize();
    for(int i = 0; i < size; i++) {
        float phase = (float(i) / float(size)) * mult;
        wavetable.addTableSample(i, (((fmodf(phase, 1.0) * 2.0f)) - 1.0f) * amplitude);
    }
}
