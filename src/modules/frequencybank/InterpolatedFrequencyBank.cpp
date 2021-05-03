#include "InterpolatedFrequencyBank.h"

InterpolatedFrequencyBank::InterpolatedFrequencyBank() {
}

void InterpolatedFrequencyBank::init(int bankCount, int bandCount, FrequencyBank::PivotPoint pivotPoint, float frequency) {
    this->bankCount = bankCount;
    this->bandCount = bandCount;
    this->baseFrequency = frequency;
    this->centreFrequency = frequency;
    for(int bankIndex = 0; bankIndex < bankCount; bankIndex++) {
        banks[bankIndex].init(bandCount, pivotPoint, frequency);
    }
}

void InterpolatedFrequencyBank::setPitchInterval(int bankIndex, int bandIndex, float interval) {
    banks[bankIndex].setPitchInterval(bandIndex, interval);
}

void InterpolatedFrequencyBank::setInterpolation(float interpolationValue) {
    interpolation.setInterpolation(interpolationValue);
}

float InterpolatedFrequencyBank::getFrequency(int bandIndex) {
    if(interpolation.interpolationIndex < bankCount-1) {
        float a = banks[interpolation.interpolationIndex].getFrequency(bandIndex);
        float b = banks[interpolation.interpolationIndex+1].getFrequency(bandIndex);
        return interpolation.interpolate(a, b);
    } else {
        return banks[bankCount-1].getFrequency(bandIndex);
    }
}