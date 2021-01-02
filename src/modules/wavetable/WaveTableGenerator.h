#ifndef WaveTableGenerator_h
#define WaveTableGenerator_h

#include "WaveTable.h"
#include <stdlib.h>

class WaveTableGenerator {
    public:
        static bool addSine(WaveTable& wavetable, float amplitude = 0.5, int mult = 1);
        static void addSquare(WaveTable& wavetable, float amplitude = 0.5, int mult = 1);

        static void pulse(WaveTable& wavetable, float pulseWidth, float amplitude = 0.5, int mult = 1);
        static void triangle(WaveTable& wavetable, float amplitude = 0.5, int mult = 1);
        static void ramp(WaveTable& wavetable, float amplitude = 0.5, int mult = 1);
};

#endif
