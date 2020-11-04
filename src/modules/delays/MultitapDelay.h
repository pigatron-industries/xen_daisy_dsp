#ifndef MultitapDelay_h
#define MultitapDelay_h

#include "TappableDelayLine.h"

#define MAX_DELAY static_cast<size_t>(48000*1)

class MultitapDelay {
    public:
        static const int MAX_TAPS = 50;

        MultitapDelay() {}
        void init(float sampleRate, float maxDelay);
        float process(float in);

        void setTapCount(int tapCount) { this->tapCount = tapCount; }
        void setTap(int tapIndex, float delayTime, float tapGain);

    private:
        float tapPositions[MAX_TAPS];
        float tapGains[MAX_TAPS];
        int tapCount;

        TappableDelayLine delayLine;

        int sampleRate;
};

#endif
