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
        LinearInput<> delayTimeInput = LinearInput<>(AnalogPin(A0), -5, 5, 0.1, 1);
        LinearInput<> feedbackInput = LinearInput<>(AnalogPin(A1), -5, 5, 0, 1);
        CrossfadeInput<> dryWetMixInput = CrossfadeInput<>(AnalogPin(A2), -5, 5);

        Delay delayLeft;
        Delay delayRight;

        int sampleRate;

        void setDelay(float delayTime);
};

#endif
