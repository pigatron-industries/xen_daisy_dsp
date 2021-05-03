#include "FrequencyBank.h"
#include "util/util.h"

FrequencyBank::FrequencyBank() {
    bandCount = 1;
    baseFrequency = 100;
    pitches[0] = 0;
}

void FrequencyBank::init(int bandCount, PivotPoint pivotPoint, float frequency) {
    this->bandCount = bandCount;
    this->pivotPoint = pivotPoint;
    this->baseFrequency = frequency;
    this->centreFrequency = frequency;
    setAllPitchIntervals(0);
}

void FrequencyBank::init(int bandCount, PivotPoint pivotPoint, float frequency, float pitchInterval) {
    this->bandCount = bandCount;
    this->pivotPoint = pivotPoint;
    this->baseFrequency = frequency;
    this->centreFrequency = frequency;
    setAllPitchIntervals(pitchInterval);
}

void FrequencyBank::setBandCount(int bandCount) {
    this->bandCount = bandCount;
}

void FrequencyBank::setFrequency(float frequency) {
    if(pivotPoint == PivotPoint::BASE) {
        this->baseFrequency = frequency;
    } else {
        this->centreFrequency = frequency;
        calcBaseFrequency(centreFrequency, pitches[bandCount-1]);
    }

    for(int i = 0; i < bandCount; i++) {
        calcFrequency(i);
    }
}

void FrequencyBank::setAllPitchIntervals(float pitchInterval) {
    if(pivotPoint == PivotPoint::CENTRE) {
        calcBaseFrequency(centreFrequency, bandCount*pitchInterval);
    }
    float pitch = 0;
    for(int i = 0; i < bandCount; i++) {
        pitches[i] = pitch;
        calcFrequency(i);
        pitch += pitchInterval;
    }
}

void FrequencyBank::setPitchInterval(int index, float interval) {
    pitches[index] = interval;
    calcFrequency(index);
}

void FrequencyBank::calcBaseFrequency(float centreFrequency, float highPitch) {
    baseFrequency = centreFrequency * powf(2, highPitch*(-0.5));
}

void FrequencyBank::calcFrequency(int index) {
    frequencies[index] = baseFrequency * powf(2, pitches[index]);
}
