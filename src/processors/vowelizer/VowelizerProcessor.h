#ifndef VowelizerProcessor_h
#define VowelizerProcessor_h

#include "Vowelizer.h"
#include "../../io/AnalogInput.h"

class VowelizerProcessor {
    public:
        VowelizerProcessor();
        void init(float sampleRate);
        void update();
        void process(float **in, float **out, size_t size);

    private:
        Vowelizer vowelizer;
        AnalogInput rangeInput;
        AnalogInput vowelInput;
        AnalogInput pitchInput;

};

#endif