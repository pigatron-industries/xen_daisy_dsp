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
        LinearInput delayInputs[10] = {
            LinearInput(A0, -5, 5, 0.001, 1),
            LinearInput(A1, -5, 5, 0.001, 1),
            LinearInput(A2, -5, 5, 0.001, 1),
            LinearInput(A3, -5, 5, 0.001, 1),
            LinearInput(A4, -5, 5, 0.001, 1),
            LinearInput(A5, -5, 5, 0.001, 1),
            LinearInput(A6, -5, 5, 0.001, 1),
            LinearInput(A7, -5, 5, 0.001, 1),
            LinearInput(A8, -5, 5, 0.001, 1),
            LinearInput(A9, -5, 5, 0.001, 1),
        };

        MultitapDelay delayLeft;
        MultitapDelay delayRight;

        int sampleRate;
};

#endif
