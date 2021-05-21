#ifndef ReverbController_h
#define ReverbController_h

#include "FDNReverb.h"
#include "Controller.h"


class ReverbController : public Controller {
    public:
        ReverbController() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        ExpInput delayInput = ExpInput(A0, 0.01);
        PowInput feedbackInput = PowInput(A1, 0.333, -5, 4.8);
        FilterInput filterInput = FilterInput(A2);
        CrossfadeInput dryWetMix = CrossfadeInput(A4, -4.8, 4.8);

        FDNReverb reverb;

        int sampleRate;

        void setDelay(float delayTime);
};

#endif
