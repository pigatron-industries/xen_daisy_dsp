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
            frequency = zeroFrequency*powf(2, voltage);
        }

        inline float getFrequency() {
            return frequency;
        }

        inline void setZeroFrequency(float _zeroFrequency) {
            zeroFrequency = _zeroFrequency;
        }

    private:
        uint8_t pin;

        uint32_t value;
        float voltage;
        float frequency;

        float zeroFrequency = 880;

};

#endif