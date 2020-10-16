#ifndef AbstractInput_h
#define AbstractInput_h

#include <inttypes.h>
#include "DaisyDuino.h"


class AbstractInput {
    public:
        AbstractInput(uint8_t _pin) : 
            pin(_pin) {
        }

        inline bool update() {
            return readVoltage();
        }

        inline bool isChanged() {
            return changed;
        }

        inline float getVoltage() {
            return voltage;
        }

        inline float getValue() {
            return voltage;
        }

    private:
        uint8_t pin;
        float smoothingWeight = 0.01;

        uint32_t value;
        float voltage;

        uint32_t prevValue;
        bool changed;

    protected:
        inline bool readVoltage() {
            prevValue = value;
            value = analogRead(pin);
            if(prevValue != value) {
                float _voltage = ((value / 1023.0) * -10.0) + 5; //represents actual voltage on input of op-amp
                voltage = smoothingWeight*_voltage + (1-smoothingWeight)*voltage;
                changed = true;
            } else {
                changed = false;
            }
            return changed;
        }
};

#endif