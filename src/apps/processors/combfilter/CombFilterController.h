#ifndef CombFilterController_h
#define CombFilterController_h

#include "Controller.h"
#include "modules/delays/Delay.h"

class CombFilterController : public Controller {
    public:
        CombFilterController() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        ExpInput<> delayTimeInput = ExpInput<>(AnalogPin(A0), 0.005);
        LinearInput<> feedbackInput = LinearInput<>(AnalogPin(A1), -5, 5, -1, 1);
        CrossfadeInput<> dryWetMixInput = CrossfadeInput<>(AnalogPin(A2), -5, 5);

        Delay delayLeft;
        Delay delayRight;

        int sampleRate;

        void setDelay(float delayTime);
};

#endif
