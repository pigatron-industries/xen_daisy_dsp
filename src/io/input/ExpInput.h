#ifndef ExpInput_h
#define ExpInput_h

#include <inttypes.h>
#include "DaisyDuino.h"
#include "AbstractInput.h"

class ExpInput : public AbstractInput {
    public:
        ExpInput(uint8_t _pin) : AbstractInput(_pin) {
        }

        ExpInput(uint8_t _pin, float midValue) : AbstractInput(_pin) {
            this->midValue = midValue;
        }

        bool update() {
            if(readVoltage()) {
                expValue = midValue*powf(2, getVoltage());
            }
            return isChanged();
        }

        float getValue() { return expValue; }
        
        void setMidValue(float midValue) { this->midValue = midValue; }

    private:
        float midValue = 523.25; //C5
        float expValue;
};

#endif