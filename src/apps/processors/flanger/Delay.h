#ifndef Delay_h
#define Delay_h

#include "DaisyDuino.h"

#define MAX_DELAY static_cast<size_t>(48000*0.1)  // 100ms

class Delay {
    public:
        Delay() {}
        void init(float sampleRate);
        float process(float in);

        void setDelay(float delayTime);
        void setFeedbackLevel(float feedbackLevel) { this->feedbackLevel = feedbackLevel; }
        void setInvertedFeedback(bool invertedFeedback) { this->invertedFeedback = invertedFeedback; }
        void setDryLevel(float dryLevel) { this->dryLevel = dryLevel; }
        void setWetLevel(float wetLevel) { this->wetLevel = wetLevel; }

    private:
        float feedbackLevel;
        bool invertedFeedback = false;
        float dryLevel = 1.0;
        float wetLevel = 0.0;

        DelayLine<float, MAX_DELAY> delayLine;

        int sampleRate;
};

#endif
