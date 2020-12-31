#ifndef DelayController_h
#define DelayController_h

#include "../../../Controller.h"
#include "../../../io/input/AnalogInput.h"
#include "../../../io/input/ExpInput.h"
#include "../../../io/input/CrossfadeInput.h"
#include "../../../modules/delays/Delay.h"

class DelayController : public Controller {
    public:
        DelayController() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        AnalogInput delayTimeInput = AnalogInput(A0, -5, 5, 0.001, 10);
        AnalogInput feedbackInput = AnalogInput(A1, -5, 5, 0, 1);
        CrossfadeInput dryWetMixInput = CrossfadeInput(A2, -5, 5);

        Delay delayLeft;
        Delay delayRight;

        int sampleRate;

        void setDelay(float delayTime);
};

#endif
