#ifndef MultitapDelayController_h
#define MultitapDelayController_h

#include "DaisyDuino.h"
#include "../../../Controller.h"
#include "../../../io/input/AnalogInput.h"
#include "../../../modules/delays/MultiTapDelay.h"


class MultitapDelayController : public Controller {
    public:
        MultitapDelayController() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        AnalogInput delayInputs[10] = {
            AnalogInput(A0, -5, 5, 0.001, 1),
            AnalogInput(A1, -5, 5, 0.001, 1),
            AnalogInput(A2, -5, 5, 0.001, 1),
            AnalogInput(A3, -5, 5, 0.001, 1),
            AnalogInput(A4, -5, 5, 0.001, 1),
            AnalogInput(A5, -5, 5, 0.001, 1),
            AnalogInput(A6, -5, 5, 0.001, 1),
            AnalogInput(A7, -5, 5, 0.001, 1),
            AnalogInput(A8, -5, 5, 0.001, 1),
            AnalogInput(A9, -5, 5, 0.001, 1),
        };

        MultitapDelay delayLeft;
        MultitapDelay delayRight;

        int sampleRate;
};

#endif
