#ifndef Spatializer_h
#define Spatializer_h

#include "DaisyDuino.h"

#define MAX_DELAY 0.001   // 10ms
#define MAX_DELAY_SAMPLES static_cast<size_t>(48000*MAX_DELAY)

class Spatializer {
    public:
        Spatializer() {}
        void init(float sampleRate);
        void process(float in);

        /* Number from -1 to 1. 0 is centre */
        void setPan(float pan);

        float getLeftOutput() { return left; }
        float getRightOutput() { return right; }

    private:
        DelayLine<float, MAX_DELAY_SAMPLES> delayLine;
        float sampleRate;
        float pan;

        float left;
        float right;
};

#endif
