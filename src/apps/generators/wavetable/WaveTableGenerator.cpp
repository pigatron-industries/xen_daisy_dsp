#include "WaveTableGenerator.h"

#include <math.h>

void WaveTableGenerator::sine(WaveTable& wavetable) {
    float* table = wavetable.getTable();
    size_t size = wavetable.getSize();

    for(int i = 0; i < size; i++) {
        float phase = float(i) / float(size);
        table[i] = sinf(phase);
    }
}
