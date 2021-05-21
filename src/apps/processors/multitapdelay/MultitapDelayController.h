#ifndef MultitapDelayController_h
#define MultitapDelayController_h

#include "Controller.h"
#include "modules/delays/MultiTapDelay.h"


class MultitapDelayController : public Controller {
    public:
        MultitapDelayController() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        LinearInput<> delayInputs[10] = {
            LinearInput<>(AnalogPin(A0), -5, 5, 0.001, 1),
            LinearInput<>(AnalogPin(A1), -5, 5, 0.001, 1),
            LinearInput<>(AnalogPin(A2), -5, 5, 0.001, 1),
            LinearInput<>(AnalogPin(A3), -5, 5, 0.001, 1),
            LinearInput<>(AnalogPin(A4), -5, 5, 0.001, 1),
            LinearInput<>(AnalogPin(A5), -5, 5, 0.001, 1),
            LinearInput<>(AnalogPin(A6), -5, 5, 0.001, 1),
            LinearInput<>(AnalogPin(A7), -5, 5, 0.001, 1),
            LinearInput<>(AnalogPin(A8), -5, 5, 0.001, 1),
            LinearInput<>(AnalogPin(A9), -5, 5, 0.001, 1),
        };

        MultitapDelay delayLeft;
        MultitapDelay delayRight;

        int sampleRate;
};

#endif
