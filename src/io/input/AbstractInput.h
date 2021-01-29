#ifndef AbstractInput_h
#define AbstractInput_h

#include <inttypes.h>
#include "DaisyDuino.h"
#include "Arduino.h"

#define SMOOTHING_FAST 0.001
#define SMOOTHING_SLOW 0.1

class AbstractInput {
    public:
        AbstractInput(uint8_t _pin) : 
            pin(_pin) {
                smoothingWeight = SMOOTHING_SLOW;
        }

        AbstractInput(uint8_t _pin, float smoothingWeight) : 
            pin(_pin) {
                this->smoothingWeight = smoothingWeight;
        }

        inline void setSmoothingWeight(float smoothingWeight) {
            this->smoothingWeight = smoothingWeight;
        }

        inline bool update() { return readVoltage(); }
        inline bool isChanged() { return changed; }
        inline float getVoltage() { return targetVoltage; }
        inline uint32_t getRawValue() { return value; }

        inline float getSmoothedVoltage() { 
            smoothedVoltage = smoothingWeight*targetVoltage + (1-smoothingWeight)*smoothedVoltage;
            return smoothedVoltage;
        }

    protected:
        uint8_t pin;
        float smoothingWeight;

        uint32_t value;
        float targetVoltage;
        float smoothedVoltage;

        bool changed;

        inline bool readVoltage() {
            uint32_t value = analogRead(pin);
            float prevVoltage = smoothedVoltage;
            targetVoltage = ((value / 4095.0) * -10.0) + 5; //represents actual voltage on input of op-amp -5v to +5v
            float diff = fabsf(targetVoltage-prevVoltage);
            if(diff > 0.02) {
                changed = true;
            } else {
                changed = false;
            }
            return changed;
        }
};

#endif