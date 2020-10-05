#ifndef CvInput_h
#define CvInput_h

#include <inttypes.h>
#include "DaisyDuino.h"


class AnalogInput {
    public:
        AnalogInput(uint8_t _pin, float _realMin, float _realMax, float _virtualMin, float _virtualMax) : 
            pin(_pin),
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

        inline void update() {
            value = analogRead(pin);
            voltage = ((value / 1023.0) * -10.0) + 5; //represents actual voltage on input of op-amp
            float _virtualValue = (((voltage - realMin) * virtualRange) / realRange) + virtualMin;
            virtualValue = smoothingWeight*_virtualValue + (1-smoothingWeight)*virtualValue;
        }

        inline float getVoltage() {
            return voltage;
        }

        inline float getValue() {
            return virtualValue;
        }

    private:
        uint8_t pin;
        float realMin;
        float realMax;
        float virtualMin;
        float virtualMax;
        float realRange;
        float virtualRange;

        float smoothingWeight = 0.01;

        uint32_t value;
        float voltage;
        float virtualValue;

};

#endif