#ifndef CvInput_h
#define CvInput_h

#include <inttypes.h>
#include "DaisyDuino.h"

class AnalogInput {
    public:
        AnalogInput(uint8_t _pin) : pin(_pin) {
        }

        inline void update() {
            value = analogRead(pin);
            voltage = ((value / 1023.0) * -10.0) + 10;
        }

        inline float getVoltage() {
            return voltage;
        }

    private:
        uint8_t pin;

        uint32_t value;
        float voltage;

};

#endif