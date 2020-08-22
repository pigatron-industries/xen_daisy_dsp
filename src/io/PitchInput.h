#ifndef PitchInput_h
#define PitchInput_h

#include <inttypes.h>
#include "DaisyDuino.h"

class PitchInput {
    public:
        PitchInput(uint8_t _pin) : pin(_pin) {
        }

        inline void update() {
            value = analogRead(pin);
            voltage = ((value / 1023.0) * -10.0) + 5;
            frequency = 880*powf(2, voltage);
        }

        inline float getFrequency() {
            return frequency;
        }

    private:
        uint8_t pin;

        uint32_t value;
        float voltage;
        float frequency;

};

#endif