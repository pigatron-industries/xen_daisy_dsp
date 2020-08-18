#include "FormantFilter.h"

FormantFilter::FormantFilter() {
}

void FormantFilter::init(float sampleRate) {
    lowPassFilter.Init(sampleRate);
    lowPassFilter.SetFreq(500.0);
    lowPassFilter.SetRes(0.85);
    lowPassFilter.SetDrive(0.8);
    highPassFilter.Init(sampleRate);
    highPassFilter.SetFreq(500.0);
    highPassFilter.SetRes(0.85);
    highPassFilter.SetDrive(0.8);
}

float FormantFilter::process(float in) {
    lowPassFilter.Process(in);
    float lowPass = lowPassFilter.Low();
    highPassFilter.Process(lowPass);
    return highPassFilter.High();
}

void FormantFilter::setFormant(Formant _formant) {
    formant = _formant;
    float lowFrequency = formant.frequency - (formant.bandwidth / 2);
    float highFrequency = formant.frequency - (formant.bandwidth / 2);
    lowPassFilter.SetFreq(highFrequency);
    highPassFilter.SetFreq(lowFrequency);
}