#ifndef InterpolatedFrequencyBank_h
#define InterpolatedFrequencyBank_h

#include "FrequencyBank.h"
#include "util/ArrayInterpolation.h"

/**
 * Represents a bank of related frequencies
 */
class InterpolatedFrequencyBank {
    public:
        static const int MAX_BANKS = 10;

        InterpolatedFrequencyBank();
        void init(int bankCount, int bandCount, FrequencyBank::PivotPoint pivotPoint, float frequency);

        void setBandCount(int bandCount);
        void setFrequency(float frequency);
        void setAllPitchIntervals(int bankIndex, float pitchInterval);
        void setPitchInterval(int bankIndex, int bandIndex, float interval);
        void setPitchOffset(int bankIndex, float pitchOffset);
        void setInterpolation(float interpolationValue);

        int getBandCount() { return bandCount; }
        float getFrequency(int bandIndex);

    protected:
        FrequencyBank::PivotPoint pivotPoint = FrequencyBank::PivotPoint::BASE;
        float baseFrequency, centreFrequency;
        int bandCount;
        int bankCount;
        FrequencyBank banks[MAX_BANKS];
        ArrayInterpolation interpolation;
};

#endif
