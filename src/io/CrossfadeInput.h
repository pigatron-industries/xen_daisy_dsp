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

        inline void update() {
            AnalogInput::update();
            dryLevel = std::sqrt(getValue());
            wetLevel = std::sqrt(1-getValue());
        }

        inline float getDryLevel() { return dryLevel; }
        inline float getWetLevel() { return wetLevel; }

    private:
        float dryLevel;
        float wetLevel;

};

#endif