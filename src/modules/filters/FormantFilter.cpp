#include "FormantFilter.h"

FormantFilter::FormantFilter() {
}

void FormantFilter::init(float sampleRate) {
    lowPassFilter.Init(sampleRate);
    lowPassFilter.SetFreq(500.0);
    lowPassFilter.SetRes(0);
    lowPassFilter.SetDrive(0);
    highPassFilter.Init(sampleRate);
    highPassFilter.SetFreq(500.0);
    highPassFilter.SetRes(0);
    highPassFilter.SetDrive(0);
}

float FormantFilter::process(float in) {
    lowPassFilter.Process(in);
    highPassFilter.Process(lowPassFilter.Low());
    return highPassFilter.High() * formant.gain;
}

void FormantFilter::setFormant(Formant _formant) {
    formant = _formant;
    float lowFrequency = formant.frequency - (formant.bandwidth / 2);
    float highFrequency = formant.frequency - (formant.bandwidth / 2);
    lowPassFilter.SetFreq(highFrequency);
    highPassFilter.SetFreq(lowFrequency);
}

void FormantFilter::setResonance(float resonance) {
    lowPassFilter.SetRes(resonance);
    highPassFilter.SetRes(resonance);
}