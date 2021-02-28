#ifndef FrequencyCounterController_h
#define FrequencyCounterController_h

#include "../../../Controller.h"
#include "../../../io/PitchOutput.h"
#include "ZeroCrossingCounter.h"

class FrequencyCounterController : public Controller {
    public:

        FrequencyCounterController() {}
        virtual void init(float sampleRate);
        virtual void update();
        virtual void updateDisplay();
        virtual void process(float **in, float **out, size_t size);

    private:
        PitchOutput pitchOutput = PitchOutput(23);

        ZeroCrossingCounter counter;

};

#endif