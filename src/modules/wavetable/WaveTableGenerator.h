#ifndef WaveTableGenerator_h
#define WaveTableGenerator_h

#include "WaveTable.h"
#include "RollOffFunction.h"
#include <stdlib.h>

class WaveTableGenerator {
    public:
        static bool addSine(deprecated::WaveTable& wavetable, float amplitude = 0.5, int mult = 1, float phaseShift = 0);
        static void addHarmonics(deprecated::WaveTable& wavetable, RollOffFunction* rolloff, float amplitude = 0.5, int mult = 1);
        static void addSquare(deprecated::WaveTable& wavetable, float amplitude = 0.5, int mult = 1);
        static void addTriangle(deprecated::WaveTable& wavetable, float amplitude = 0.5, int mult = 1);
        static void addRamp(deprecated::WaveTable& wavetable, float amplitude = 0.5, int mult = 1);
        static void addPulse(deprecated::WaveTable& wavetable, float amplitude = 0.5, int mult = 1);
        static void addImpulse(deprecated::WaveTable& wavetable, float amplitude = 0.5, int mult = 1);
        static void addViolin(deprecated::WaveTable& wavetable, float amplitude = 0.5, int mult = 1);

        static void pulse(deprecated::WaveTable& wavetable, float pulseWidth, float amplitude = 0.5, int mult = 1);
        static void triangle(deprecated::WaveTable& wavetable, float amplitude = 0.5, int mult = 1);
        static void ramp(deprecated::WaveTable& wavetable, float amplitude = 0.5, int mult = 1);
};

#endif
