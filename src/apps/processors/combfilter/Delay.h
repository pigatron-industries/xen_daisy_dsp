#ifndef Delay_h
#define Delay_h

#include "DaisyDuino.h"
#include "../../../modules/delays/TappableDelayLine.h"

class Delay {
    public:
        Delay() {}
        void init(float sampleRate, float maxDelay);
        float process(float in);

        void setDelay(float delayTime);
        void setFeedbackLevel(float feedbackLevel) { this->feedbackLevel = feedbackLevel; }
        void setDryLevel(float dryLevel) { this->dryLevel = dryLevel; }
        void setWetLevel(float wetLevel) { this->wetLevel = wetLevel; }

    private:
        float feedbackLevel;
        float dryLevel = 1.0;
        float wetLevel = 0.0;

        TappableDelayLine delayLine;

        float sampleRate;
        float maxDelay;
};

#endif
