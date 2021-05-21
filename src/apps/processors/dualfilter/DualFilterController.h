#ifndef FilterController_h
#define FilterController_h

#include <RotaryEncoder.h>
#include "Controller.h"
#include "modules/filters/FilterWrapper.h"
#include "io/Hardware.h"

class DualFilterController : public Controller {
    public:
        DualFilterController() {}
        virtual void init(float sampleRate);
        virtual void update();
        virtual void updateDisplay();
        virtual void event(UIEvent event, int itemIndex);
        virtual void process(float **in, float **out, size_t size);

    private:
        ExpInput frequencyInput1 = ExpInput(A0);
        LinearInput resonanceInput1 = LinearInput(A2, -5, 5, 0.001, 1);
        ExpInput frequencyInput2 = ExpInput(A1);
        LinearInput resonanceInput2 = LinearInput(A3, -5, 5, 0.001, 1);

        FilterWrapper filter1;
        FilterWrapper filter2;

        String getFilterTypeText(FilterWrapper::FilterType type);
};

#endif
