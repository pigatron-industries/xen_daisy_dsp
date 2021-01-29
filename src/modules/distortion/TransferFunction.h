#ifndef TransferFunction_h
#define TransferFunction_h

/**
 * A TransferFunction is a a function which takes a value 0->1 and returns a value from 0->1
 */
class TransferFunction
{
    public:
        virtual float process(float in) = 0;
};

#endif