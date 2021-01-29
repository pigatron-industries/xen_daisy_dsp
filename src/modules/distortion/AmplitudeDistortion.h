#ifndef AmplitudeDistortion_h
#define AmplitudeDistortion_h

#include "TransferFunction.h"

class AmplitudeDistortion
{
    public:
        float init(TransferFunction* transferFunction) { transferFunction = transferFunction; }
        float process(float in);

    private:
        TransferFunction* transferFunction;
};

#endif