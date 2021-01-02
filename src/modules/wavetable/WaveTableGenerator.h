#ifndef WaveTableGenerator_h
#define WaveTableGenerator_h

#include "WaveTable.h"
#include <stdlib.h>

class WaveTableGenerator {
    public:
        static void sine(WaveTable& wavetable, float amplitude = 0.5, int mult = 1);
        static bool blSine(WaveTable& wavetable, float amplitude = 0.5, int mult = 1);
        static void square(WaveTable& wavetable, float pulseWidth, float amplitude = 0.5, int mult = 1);
        static void blSquare(WaveTable& wavetable, float amplitude = 0.5, int mult = 1);
        static void triangle(WaveTable& wavetable, float amplitude = 0.5, int mult = 1);
        static void ramp(WaveTable& wavetable, float amplitude = 0.5, int mult = 1);
};

#endif
