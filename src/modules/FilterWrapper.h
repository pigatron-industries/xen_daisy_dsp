#ifndef FilterWrapper_h
#define FilterWrapper_h

#include "DaisyDuino.h"



class FilterWrapper {
    public:

        enum FilterType {
            SVF_BAND_PASS,
            SVF_LOW_PASS,
            SVF_HIGH_PASS,
            SVF_NOTCH,
            SVF_PEAK,
            BIQUAD_BAND_PASS,
            MOOG_LADDER
        };

        FilterWrapper() {}
        void init(float sampleRate);
        float process(float in);

        FilterType getType() { return filterType; } 

        void setType(FilterType filterType);
        void setFrequency(float frequency);
        void setResonance(float resonance);

    private:
        FilterType filterType;
        float frequency;
        float resonance;

        Svf svfFilter;
        Biquad biquadFilter;
        MoogLadder moogLadderFilter;

};

#endif