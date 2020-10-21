#include "FilterBank.h"


void FilterBank::init(float sampleRate) {
    for(int i = 0; i < MAX_FILTER_COUNT; i++) {
        filters[i].init(sampleRate);
    }
}

float FilterBank::process(float in) {
    if(processOrder == ProcessOrder::PARALLEL) {
        return processParallel(in);
    } else {
        return processSerial(in);
    }
}

float FilterBank::processSerial(float in) {
    float out = in;
    for(int i = 0; i < size; i++) {
        out = filters[i].process(out);
    }
    return out;
}

float FilterBank::processParallel(float in) {
    odd = 0;
    even = 0;
    for(int i = 0; i < size; i++) {
        float out = filters[i].process(in);
        if(i%2 == 0) {
            even += out;
        } else {
            odd += out;
        }
    }
    all = odd + even;
    return all;
}

void FilterBank::setFilterResonance(int index, float resonance) {
    filters[index].setResonance(resonance);
}

void FilterBank::setFilterFrequency(int index, float frequency) {
    filters[index].setFrequency(frequency);
}

void FilterBank::setFilterGain(int index, float gain) {
    filters[index].setGain(gain);
}

void FilterBank::setBankBandPass(float firstFrequency, float frequencyRatio) {
    float frequency = firstFrequency;
    for(int i = 0; i < size; i++) {
        filters[i].setType(FilterWrapper::FilterType::SVF_BAND_PASS);
        filters[i].setFrequency(frequency);
        filters[i].setGain(1);
        filters[i].setResonance(0);
        frequency = frequency * frequencyRatio;
    }
    processOrder = ProcessOrder::PARALLEL;
}

void FilterBank::setBankLowBandHighPass(float lowPassFrequency, float highPassFrequency, float firstBandFrequency, float frequencyRatio) {
    float frequency = firstBandFrequency;
    for(int i = 1; i < size-1; i++) {
        filters[i].setType(FilterWrapper::FilterType::SVF_BAND_PASS);
        filters[i].setFrequency(frequency);
        filters[i].setGain(1);
        filters[i].setResonance(0);
        frequency = frequency * frequencyRatio;
    }
    filters[0].setType(FilterWrapper::FilterType::SVF_LOW_PASS);
    filters[0].setFrequency(lowPassFrequency);
    filters[0].setGain(1);
    filters[0].setResonance(1);
    filters[size-1].setType(FilterWrapper::FilterType::SVF_HIGH_PASS);
    filters[size-1].setFrequency(highPassFrequency);
    filters[size-1].setGain(1);
    filters[size-1].setResonance(0);
    processOrder = ProcessOrder::PARALLEL;
}