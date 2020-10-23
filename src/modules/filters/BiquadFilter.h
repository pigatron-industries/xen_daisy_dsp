#ifndef Biquad2_h
#define Biquad2_h

#include <math.h>

//
//  Biquad.h
//
//  Created by Nigel Redmon on 11/24/12
//  EarLevel Engineering: earlevel.com
//  Copyright 2012 Nigel Redmon
//
//  For a complete explanation of the Biquad code:
//  http://www.earlevel.com/main/2012/11/26/biquad-c-source-code/
//
//  License:
//
//  This source code is provided as is, without warranty.
//  You may copy and distribute verbatim copies of this document.
//  You may modify and use this source code to create binary code
//  for your own purposes, free or commercial.
//

class BiquadFilter
{
    public:
        enum FilterType {
            LOWPASS = 0,
            HIGHPASS,
            BANDPASS,
            NOTCH,
            PEAK,
            LOWSHELF,
            HIGHSHELF
        };

        BiquadFilter();
        void init(float sample_rate);

        void setType(FilterType type);
        void setQ(float q);
        void setFrequency(float frequency);
        void setPeakGain(float peakGainDB);
        void setBiquad(FilterType type, float frequency, float q, float peakGainDB);
        float process(float in);

        float getFrequency() { return frequency; }

    private:
        void calcBiquad();

        FilterType type;
        float sampleRate;
        float frequency;
        float a0, a1, a2, b1, b2;
        float fc, q, peakGain;
        float z1, z2;
        float out;
};


inline float BiquadFilter::process(float in) {
    out = in * a0 + z1;
    z1 = in * a1 + z2 - b1 * out;
    z2 = in * a2 - b2 * out;
    return out;
}

#endif