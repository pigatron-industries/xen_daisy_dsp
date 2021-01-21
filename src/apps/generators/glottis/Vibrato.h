#ifndef Vibrato_h
#define Vibrato_h

#include <inttypes.h>


class Vibrato {
    public:
        void init(float sampleRate);
        float process();
        void update();
        void setTargetValue(float targetValue) { this->targetValue = targetValue; }
        void setNoiseAmount(float noiseAmount) { this->noiseAmount = noiseAmount; }
        void setVibratoAmount(float amount) { this->vibratoAmount = amount; }
        void setFrequency(float frequency) { this->vibratoFrequency = frequency; }

    private:
        float value, oldValue, newValue, smoothValue, targetValue;
        float updatePeriod;
        float lambdaStep, lambda;
        float totalTime;
        float noiseAmount;
        float vibratoAmount;
        float vibratoFrequency;
        float sampleRate;
        float timeStep;
};

#endif