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

void FormantFilter::setFormant(Formant _formant) {
    //TODO: set filter parameters
}