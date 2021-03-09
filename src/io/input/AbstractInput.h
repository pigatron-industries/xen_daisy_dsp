#ifndef AbstractInput_h
#define AbstractInput_h

#include <inttypes.h>
#include "Arduino.h"
#include "util/util.h"

#define SMOOTHING_FAST 0.0005
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
            smoothedVoltage = smooth(targetVoltage, smoothedVoltage, smoothingWeight);
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
            float newVoltage = ((value / 4095.0) * -10.0) + 5; //represents actual voltage on input of op-amp -5v to +5v
            float diff = fabsf(newVoltage-prevVoltage);
            if(diff > 0.02) {
                changed = true;
                targetVoltage = newVoltage;
            } else {
                changed = false;
            }
            return changed;
        }
};

#endif