#ifndef FilterController_h
#define FilterController_h

#include <RotaryEncoder.h>
#include "../../../Controller.h"
#include "../../../modules/filters/FilterWrapper.h"
#include "../../../io/input/AnalogInput.h"
#include "../../../io/input/PitchInput.h"
#include "../../../io/Hardware.h"

class DualFilterController : public Controller {
    public:
        DualFilterController() {}
        virtual void init(float sampleRate);
        virtual void update();
        virtual void updateDisplay();
        virtual void event(UIEvent event, int itemIndex);
        virtual void process(float **in, float **out, size_t size);

    private:
        PitchInput frequencyInput1 = PitchInput(A0);
        AnalogInput resonanceInput1 = AnalogInput(A2, -5, 5, 0.001, 1);
        PitchInput frequencyInput2 = PitchInput(A1);
        AnalogInput resonanceInput2 = AnalogInput(A3, -5, 5, 0.001, 1);

        FilterWrapper filter1;
        FilterWrapper filter2;

        String getFilterTypeText(FilterWrapper::FilterType type);
};

#endif
