#ifndef PowInput_h
#define PowInput_h

#include <inttypes.h>
#include "AnalogInput.h"

class PowInput : public AnalogInput {
    public:
        PowInput(uint8_t pin, float power, float realMin, float realMax) : AnalogInput(pin, realMin, realMax, 0, 1) {
            this->power = power;
        }

        float getValue() { 
            powValue = powf(AnalogInput::getValue(), power);
            return powValue;
        }

    private:
        float power;
        float powValue;
};

#endif