#ifndef PowerFunction_h
#define PowerFunction_h

#include "TransferFunction.h"

class PowerFunction : public TransferFunction
{
    public:
        void setPower(float power) { this->power = power; }
        virtual float process(float in);
    private:
        float power = 1;
};

#endif