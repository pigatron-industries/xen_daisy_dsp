#ifndef VocoderController_h
#define VocoderController_h

#include "Vocoder.h"
#include "../../../Controller.h"
#include "../../../io/input/AnalogInput.h"

class VocoderController : public Controller {
    public:
        VocoderController() {}
        virtual void init(float sampleRate);
        virtual void update();
        virtual void updateDisplay();
        virtual void process(float **in, float **out, size_t size);

    private:
        AnalogInput resonanceInput = AnalogInput(A0, -5, 5, 0, 1);
        AnalogInput frequencyBaseInput = AnalogInput(A1, -5, 5, 55.0, 220.0);
        AnalogInput pitchIntervalInput = AnalogInput(A2, -5, 5, 0.25, 1.0);
        AnalogInput bandsInput = AnalogInput(A3, -5, 5, 1, 20.5); 

        Vocoder vocoder;

};

#endif
