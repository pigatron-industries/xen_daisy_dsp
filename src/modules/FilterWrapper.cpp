#include "FilterWrapper.h"


void FilterWrapper::init(float sampleRate) {
    svfFilter.init(sampleRate);
    moogLadderFilter.Init(sampleRate);
    biquadFilter.init(sampleRate);
}

float FilterWrapper::process(float in) {
    switch(filterType) {
        case SVF_BAND_PASS:
            svfFilter.process(in);
            return svfFilter.band() * gain;
        case SVF_LOW_PASS:
            svfFilter.process(in);
            return svfFilter.low() * gain;
        case SVF_HIGH_PASS:
            svfFilter.process(in);
            return svfFilter.high() * gain;
        case SVF_NOTCH:
            svfFilter.process(in);
            return svfFilter.notch();
        case SVF_PEAK:
            svfFilter.process(in);
            return svfFilter.peak();
        case BIQUAD:
            return biquadFilter.process(in);
        case MOOG_LADDER:
            return moogLadderFilter.Process(in);
    }
}

void FilterWrapper::setType(FilterType filterType) {
    this->filterType = filterType;
    setFrequency(frequency);
    setResonance(resonance);
}

void FilterWrapper::setFrequency(float frequency) {
    this->frequency = frequency;
    switch(filterType) {
        case SVF_BAND_PASS:
        case SVF_LOW_PASS:
        case SVF_HIGH_PASS:
        case SVF_NOTCH:
        case SVF_PEAK:
            svfFilter.setFrequency(frequency);
            break;
        case BIQUAD:
            biquadFilter.setFrequency(frequency);
            break;
        case MOOG_LADDER:
            moogLadderFilter.SetFreq(frequency);
            break;
    }
}

void FilterWrapper::setResonance(float resonance) {
    this->resonance = resonance;
    switch(filterType) {
        case SVF_BAND_PASS:
        case SVF_LOW_PASS:
        case SVF_HIGH_PASS:
        case SVF_NOTCH:
        case SVF_PEAK:
            svfFilter.setResonance(resonance);
            break;
        case BIQUAD:
            biquadFilter.setQ(resonance*2);
            break;
        case MOOG_LADDER:
            moogLadderFilter.SetRes(resonance);
            break;
    }
}

void FilterWrapper::setGain(float gain) {
    this->gain = gain;
}