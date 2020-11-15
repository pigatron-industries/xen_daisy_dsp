#ifndef AllPassFilter_h
#define AllPassFilter_h

#include "MultitapDelay.h"

class AllPassFilter {
    public:
        AllPassFilter() {}
        void init(float sampleRate, float maxDelay);
        float process(float in);

        void setDelayTime(float delayTime);
        void setFeedback(float feedback) { this->feedback = feedback; }

    private:
        MultitapDelay delay;

        float sampleRate;

        int fs;
        float delayLength;
        float feedback = 0.5;

        float delayedSample = 0;
        float feedForwardSample = 0;
};

inline float AllPassFilter::process(float in) {
    delayedSample = delay.read();
    delay.write(in + (delayedSample * feedback));
    feedForwardSample = in * -feedback;
    return (delayedSample + feedForwardSample);
}

#endif
