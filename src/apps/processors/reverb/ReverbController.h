#ifndef ReverbController_h
#define ReverbController_h

// #include "DaisyDuino.h"
#include "FDNReverb.h"
#include "../../../Controller.h"
#include "../../../io/input/AnalogInput.h"
#include "../../../io/input/CrossfadeInput.h"
#include "../../../io/input/FilterInput.h"


class ReverbController : public Controller {
    public:
        ReverbController() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        AnalogInput feedbackInput = AnalogInput(A0, -5, 5, 0.0001, 1);
        CrossfadeInput dryWetMix = CrossfadeInput(A1, -5, 5);
        FilterInput filterInput = FilterInput(A2);
        AnalogInput delayInput = AnalogInput(A3, -5, 5, 0.0005, 0.05);

        FDNReverb reverbLeft;
        FDNReverb reverbRight;
        //AllPassFilter allPassFilter;

        int sampleRate;

        void setDelay(float delayTime);
};

#endif
