#ifndef FlangerController_h
#define FlangerController_h

#include "../../../Controller.h"
#include "../../../io/input/AnalogInput.h"
#include "../../../io/input/CrossfadeInput.h"
#include "Delay.h"

class FlangerController : public Controller {
    public:
        FlangerController() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        AnalogInput delayTimeInput = AnalogInput(A0, -5, 5, 0.0001, 0.01);
        AnalogInput feedbackInput = AnalogInput(A1, -5, 5, 0, 1);
        CrossfadeInput dryWetMixInput = CrossfadeInput(A2, -5, 5);
        bool invertedFeedback = false;

        Delay delayLeft;
        Delay delayRight;

        int sampleRate;

        void setDelay(float delayTime);
};

#endif
