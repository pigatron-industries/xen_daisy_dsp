#ifndef TractProcessor_h
#define TractProcessor_h

#include "Tract.h"
#include "../../io/AnalogInput.h"
#include "../../modules/BiquadFilter.h"

class TractProcessor {
    public:
        TractProcessor();
        void init(float sampleRate);
        void update();
        void process(float **in, float **out, size_t size);

    private:
        Tract tract;
        WhiteNoise whiteNoise;
        BiquadFilter fricativeFilter;

        AnalogInput tongueX;
        AnalogInput tongueY;
        AnalogInput constrictionX;
        AnalogInput constrictionY;

        float fricativeIntensity = 0.0;

};

#endif
