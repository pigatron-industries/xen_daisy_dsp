#ifndef CombFilterController_h
#define CombFilterController_h

#include "../../../Controller.h"
#include "../../../io/input/AnalogInput.h"
#include "../../../io/input/ExpInput.h"
#include "../../../io/input/CrossfadeInput.h"
#include "Delay.h"

class CombFilterController : public Controller {
    public:
        CombFilterController() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        ExpInput delayTimeInput = ExpInput(A0, 0.005);
        AnalogInput feedbackInput = AnalogInput(A1, -5, 5, -1, 1);
        CrossfadeInput dryWetMixInput = CrossfadeInput(A2, -5, 5);
        bool invertedFeedback = false;

        Delay delayLeft;
        Delay delayRight;

        int sampleRate;

        void setDelay(float delayTime);
};

#endif
