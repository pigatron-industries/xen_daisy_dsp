#ifndef VocoderController_h
#define VocoderController_h

#include "Vocoder.h"
#include "../../../Controller.h"
#include "../../../io/AnalogInput.h"

class VocoderController : public Controller {
    public:
        VocoderController() {}
        virtual void init(float sampleRate);
        virtual void update();
        virtual void updateDisplay();
        virtual void process(float **in, float **out, size_t size);

    private:
        AnalogInput resonanceInput = AnalogInput(A0, -5, 5, 0, 1);
        AnalogInput frequencyRatio = AnalogInput(A1, -5, 5, 0.25, 1);

        Vocoder vocoder;

};

#endif
