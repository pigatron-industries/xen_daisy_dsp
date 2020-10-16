#ifndef PitchInput_h
#define PitchInput_h

#include <inttypes.h>
#include "DaisyDuino.h"
#include "AbstractInput.h"

class PitchInput : public AbstractInput {
    public:
        PitchInput(uint8_t _pin) : AbstractInput(_pin) {
        }

        PitchInput(uint8_t _pin, float zeroFrequency) : AbstractInput(_pin) {
            this->zeroFrequency = zeroFrequency;
        }

        inline bool update() {
            if(readVoltage()) {
                frequency = zeroFrequency*powf(2, getVoltage());
            }
            return isChanged();
        }

        inline float getFrequency() {
            return frequency;
        }

        inline void setZeroFrequency(float _zeroFrequency) {
            zeroFrequency = _zeroFrequency;
        }

    private:
        float zeroFrequency = 880;
        float frequency;
};

#endif