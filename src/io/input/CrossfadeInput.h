#ifndef CrossfadeInput_h
#define CrossfadeInput_h

#include <inttypes.h>
#include "DaisyDuino.h"
#include "AnalogInput.h"

class CrossfadeInput : public AnalogInput {
    public:
        CrossfadeInput(uint8_t _pin, float _realMin, float _realMax) : 
            AnalogInput(_pin, _realMin, _realMax, 0, 1) {
        }

        inline bool update() {
            if(AnalogInput::update()) {
                dryLevel = sqrtf(getValue());
                wetLevel = sqrtf(1-getValue());
            }
            return isChanged();
        }

        inline float getDryLevel() { return dryLevel; }
        inline float getWetLevel() { return wetLevel; }

    private:
        float dryLevel;
        float wetLevel;

};

#endif