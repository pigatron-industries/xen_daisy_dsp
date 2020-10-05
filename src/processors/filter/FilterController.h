#ifndef FilterController_h
#define FilterController_h

#include <RotaryEncoder.h>
#include "../Controller.h"
#include "../../modules/FilterWrapper.h"
#include "../../io/AnalogInput.h"
#include "../../io/PitchInput.h"

class FilterController : public Controller {
    public:
        FilterController(RotaryEncoder& encoder) : encoder(encoder) {}
        void init(float sampleRate);
        void update();
        void process(float **in, float **out, size_t size);

    private:
        RotaryEncoder& encoder;
        PitchInput frequencyInput = PitchInput(A0);
        AnalogInput resonanceInput = AnalogInput(A1, -5, 5, 0.001, 1);
        AnalogInput feedbackInput = AnalogInput(A2, -5, 5, 0, 1);

        FilterWrapper filter;

};

#endif
