#ifndef FDNReverb_h
#define FDNReverb_h

#include "../../../modules/delays/AllPassFilter.h"
#include "../../../modules/delays/MultiTapDelay.h"
#include "../../../modules/filters/StateVariableFilter.h"


class FDNReverb {
    public:
        static const int DELAY_LINES = 4;
        FDNReverb() {}
        void init(float sampleRate);
        float process(float in);

        void setDryLevel(float dryLevel) { dryOut = dryLevel; }
        void setWetLevel(float wetLevel) { wetOut = wetLevel; }
        void setFeedback(float feedbackGain) { this->feedbackGain = feedbackGain; }
        void setDelay(float delay);
        void setLowPassFilterFrequency(float frequency);
        void setHighPassFilterFrequency(float frequency);
        void setLowPassFilter(bool lowPass) { this->lowPass = lowPass; }
        void setHighPassFilter(bool highPass) { this->highPass = highPass; }

        void modulate();

    private:

        StateVariableFilter lowPassFilter[DELAY_LINES];
        StateVariableFilter highPassFilter[DELAY_LINES];
        AllPassFilter allPassFilter[DELAY_LINES];
        MultitapDelay multitapDelay[DELAY_LINES];
        float delayTimes[DELAY_LINES] = { 0.53, 0.67, 0.79, 0.97 };

        int feedbackMatrix[4][4] = {
            { 0,  1,  1,  0}, 
            {-1,  0,  0, -1},
            { 1,  0,  0, -1},
            { 0,  1, -1,  0}
        };

        int sampleRate;

        float modPhase = 0;
        float modRate = 10; //Hz
        float modDepth = 0.05; //Multiplier of delay time
        float mod[DELAY_LINES];

        int modUpdateSamples = 48;
        int modUpdateCounter = 0;
        float modUpdateTime;

        float delayTime = 0.1;
        float feedbackGain = 0.5;
        float dryOut = 0.5;
        float wetOut = 0.5;
        bool lowPass = false;
        bool highPass = false;
};

#endif
