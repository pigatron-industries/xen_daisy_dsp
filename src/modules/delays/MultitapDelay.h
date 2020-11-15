#ifndef MultitapDelay_h
#define MultitapDelay_h

#include "TappableDelayLine.h"

class MultitapDelay {
    public:
        static const int MAX_TAPS = 50;

        MultitapDelay() {}
        void init(float sampleRate, float maxDelay);
        float process(float in);

        void write(float in);
        float readTap(int index);
        float read() { return readTap(0); }

        void setDryGain(float dryGain) { this->dryGain = dryGain; }
        void setTapCount(int tapCount) { this->tapCount = tapCount; }
        void setTap(int tapIndex, float delayTime, float tapGain);
        void setTap(int tapIndex, float delayTime);
        void setDelayTime(float delayTime);

        void createTaps(int tapCount, float tapLength, float tapDecay, float tapGain);

    private:
        float tapPositions[MAX_TAPS];
        float tapGains[MAX_TAPS];
        float dryGain = 0.2;
        int tapCount;

        TappableDelayLine delayLine;

        int sampleRate;
};


inline void MultitapDelay::write(float in) {
    delayLine.write(in);
}

inline float MultitapDelay::readTap(int index) {
    return delayLine.read(tapPositions[index]) * tapGains[index];  
}


#endif
