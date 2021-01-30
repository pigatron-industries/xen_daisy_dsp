#ifndef FDNReverb_h
#define FDNReverb_h

#include "../../../modules/filters/AllPass.h"
#include "../../../modules/delays/MultiTapDelay.h"
#include "../../../modules/filters/StateVariableFilter.h"
#include "../../../util/util.h"


class FDNReverb {
    public:
        static const int DELAY_LINES = 4;
        static const int ALL_PASS_FILTERS = 6;
        FDNReverb() {}
        void init(float sampleRate);
        void process(float in);
        float getOutput(int channel);

        void setDryLevel(float dryLevel) { this->dryLevel = dryLevel; }
        void setWetLevel(float wetLevel) { this->wetLevel = wetLevel; }
        void setFeedback(float feedbackGain) { this->feedbackGain = feedbackGain; }
        void setDelay(float delay);
        void setLowPassFilterFrequency(float frequency);
        void setHighPassFilterFrequency(float frequency);
        void setLowPassFilter(bool lowPass) { this->lowPass = lowPass; }
        void setHighPassFilter(bool highPass) { this->highPass = highPass; }

        void modulate();

    public:

        float input[DELAY_LINES];
        float output[DELAY_LINES];

        StateVariableFilter lowPassFilter[DELAY_LINES];
        StateVariableFilter highPassFilter[DELAY_LINES];
        AllPass allPassFilter[DELAY_LINES][ALL_PASS_FILTERS];
        MultitapDelay multitapDelay[DELAY_LINES];

        float delayTimes[DELAY_LINES] = { 0.53, 0.97, 0.79, 0.67 };


        // static constexpr float feedbackMultiplier = 1;
        // int feedbackMatrix[4][4] = {
        //     { 0,  1,  1,  0}, 
        //     {-1,  0,  0, -1},
        //     { 1,  0,  0, -1},
        //     { 0,  1, -1,  0}
        // };

        static constexpr float feedbackMultiplier = ONE_OVER_ROOT_TWO;
        int feedbackMatrix[4][4] = {
            { 1,  1,  1,  1}, 
            {-1,  1,  -1, 1},
            {-1,  -1,  1, 1},
            { 1,  -1, -1, 1}
        };

        // static constexpr float feedbackMultiplier = ONE_OVER_ROOT_TWO;
        // int feedbackMatrix[4][4] = {
        //     { 1, -1, -1, -1}, 
        //     {-1,  1, -1, -1},
        //     {-1, -1,  1, -1},
        //     {-1, -1, -1,  1}
        // };

        int sampleRate;
        float sampleTime;

        float modRate = 5; //Hz
        float modDepth = 0.001; //Multiplier of delay time
        float mod[DELAY_LINES];
        float modPhase[DELAY_LINES];

        float delayTime = 0.1;
        float feedbackGain = 0.5;
        float dryLevel = 0.5;
        float wetLevel = 0.5;
        bool lowPass = false;
        bool highPass = false;
};

#endif
