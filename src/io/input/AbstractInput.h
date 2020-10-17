#ifndef AbstractInput_h
#define AbstractInput_h

#include <inttypes.h>
#include "DaisyDuino.h"
#include "Arduino.h"

class AbstractInput {
    public:
        AbstractInput(uint8_t _pin) : 
            pin(_pin) {
        }

        inline bool update() { return readVoltage(); }
        inline bool isChanged() { return changed; }
        inline float getVoltage() { return voltage; }
        inline float getValue() { return voltage; }
        inline uint32_t getRawValue() { return value; }

    private:
        uint8_t pin;
        float smoothingWeight = 0.02;

        uint32_t value;
        float voltage;
        float prevVoltage;

        bool changed;

    protected:
        inline bool readVoltage() {
            uint32_t value = analogRead(pin);
            float newVoltage = ((value / 4095.0) * -10.0) + 5; //represents actual voltage on input of op-amp -5v to +5v
            voltage = smoothingWeight*newVoltage + (1-smoothingWeight)*voltage;
            float diff = fabsf(prevVoltage-voltage);
            if(diff > 0.01) {
                prevVoltage = voltage;
                changed = true;
            } else {
                changed = false;
            }
            return changed;
        }
};

#endif