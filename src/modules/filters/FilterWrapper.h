#ifndef FilterWrapper_h
#define FilterWrapper_h

#include <DaisyDSP.h>
#include "BiquadFilter.h"
#include "StateVariableFilter.h"

/**
 * Wrapper around various filter types so that they can be easily switched. 
 **/
class FilterWrapper {
    public:

        enum FilterType {
            SVF_BAND_PASS,
            SVF_LOW_PASS,
            SVF_HIGH_PASS,
            SVF_NOTCH,
            SVF_PEAK,
            BIQUAD,
            MOOG_LADDER
        };

        FilterWrapper() {}
        void init(float sampleRate);
        float process(float in);

        FilterType getType() { return filterType; } 

        void setType(FilterType filterType);
        void setFrequency(float frequency);
        void setResonance(float resonance);
        void setGain(float gain);

        float getFrequency() { return frequency; };

    private:
        FilterType filterType;
        float frequency;
        float resonance = 0;
        float gain = 1;

        StateVariableFilter svfFilter;
        BiquadFilter biquadFilter;
        daisysp::MoogLadder moogLadderFilter;

};

#endif