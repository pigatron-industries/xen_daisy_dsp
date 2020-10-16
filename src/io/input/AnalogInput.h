#ifndef AnalogInput_h
#define AnalogInput_h

#include <inttypes.h>
#include "DaisyDuino.h"
#include "AbstractInput.h"


class AnalogInput : public AbstractInput {
    public:
        AnalogInput(uint8_t _pin, float _realMin, float _realMax, float _virtualMin, float _virtualMax) : 
            AbstractInput(_pin),
            realMin(_realMin),
            realMax(_realMax),
            virtualMin(_virtualMin),
            virtualMax(_virtualMax)  {
                realRange = realMax - realMin;
                virtualRange = virtualMax - virtualMin;
        }

        void setRange(float _virtualMin, float _virtualMax) {
            virtualMin = _virtualMin;
            virtualMax = _virtualMax;
            virtualRange = virtualMax - virtualMin;
        }

        inline bool update() {
            if(readVoltage()) {
                virtualValue = (((getVoltage() - realMin) * virtualRange) / realRange) + virtualMin;
            }
            return isChanged();
        }

        inline float getValue() {
            return virtualValue;
        }

    private:
        float realMin;
        float realMax;
        float virtualMin;
        float virtualMax;
        float realRange;
        float virtualRange;

        float virtualValue;
};

#endif