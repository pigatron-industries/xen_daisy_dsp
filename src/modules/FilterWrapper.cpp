#include "FilterWrapper.h"


void FilterWrapper::init(float sampleRate) {
    svfFilter.Init(sampleRate);
    moogLadderFilter.Init(sampleRate);
    biquadFilter.init(sampleRate);
}

float FilterWrapper::process(float in) {
    switch(filterType) {
        case SVF_BAND_PASS:
            svfFilter.Process(in);
            return svfFilter.Band() * gain;
        case SVF_LOW_PASS:
            svfFilter.Process(in);
            return svfFilter.Low() * gain;
        case SVF_HIGH_PASS:
            svfFilter.Process(in);
            return svfFilter.High() * gain;
        case SVF_NOTCH:
            svfFilter.Process(in);
            return svfFilter.Notch();
        case SVF_PEAK:
            svfFilter.Process(in);
            return svfFilter.Peak();
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
            svfFilter.SetFreq(frequency);
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
            svfFilter.SetRes(resonance);
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