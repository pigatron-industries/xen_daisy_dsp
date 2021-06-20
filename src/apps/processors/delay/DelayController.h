#ifndef DelayController_h
#define DelayController_h

#include "Controller.h"
#include "modules/delays/Delay.h"

class DelayController : public Controller {
    public:
        DelayController() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        LinearInput<> delayTimeLeftInput = LinearInput<>(AnalogInputPin(A0), -5, 5, 0.1, 1);
        LinearInput<> delayTimeRightInput = LinearInput<>(AnalogInputPin(A1), -5, 5, 0.1, 1);
        LinearInput<> feedbackInput = LinearInput<>(AnalogInputPin(A2), -5, 5, 0, 1);
        CrossfadeInput<> dryWetMixInput = CrossfadeInput<>(AnalogInputPin(A3), -5, 5);

        SlewLimiter delayLeftSlewLimiter;
        SlewLimiter delayRightSlewLimiter;

        Delay delayLeft;
        Delay delayRight;

        int sampleRate;

        void setDelay(float delayTime);
};

#endif
