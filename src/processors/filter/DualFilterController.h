#ifndef FilterController_h
#define FilterController_h

#include <RotaryEncoder.h>
#include "../Controller.h"
#include "../../modules/FilterWrapper.h"
#include "../../io/AnalogInput.h"
#include "../../io/PitchInput.h"
#include "../../io/Hardware.h"

class DualFilterController : public Controller {
    public:
        DualFilterController(Hardware& hardware) : Controller(hardware, "Dual Filter") {}
        virtual void init(float sampleRate);
        virtual void update();
        virtual void process(float **in, float **out, size_t size);
        virtual void render();

    private:
        PitchInput frequencyInput1 = PitchInput(A0);
        AnalogInput resonanceInput1 = AnalogInput(A1, -5, 5, 0.001, 1);
        PitchInput frequencyInput2 = PitchInput(A2);
        AnalogInput resonanceInput2 = AnalogInput(A3, -5, 5, 0.001, 1);

        FilterWrapper filter1;
        FilterWrapper filter2;

        int selectedChannel = 0;

        void printFilterType(FilterWrapper::FilterType type);
        void renderFrequencies();
};

#endif
