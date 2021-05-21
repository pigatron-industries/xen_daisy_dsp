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
        ExpInput<> delayInput = ExpInput<>(AnalogPin(A0), 0.01);
        PowInput<> feedbackInput = PowInput<>(AnalogPin(A1), 0.333, -5, 4.8);
        FilterInput<> filterInput = FilterInput<>(AnalogPin(A2));
        CrossfadeInput<> dryWetMix = CrossfadeInput<>(AnalogPin(A4), -4.8, 4.8);

        FDNReverb reverb;

        int sampleRate;

        void setDelay(float delayTime);
};

#endif
