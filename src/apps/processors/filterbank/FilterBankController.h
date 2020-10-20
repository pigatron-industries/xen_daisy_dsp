#ifndef FilterBankController_h
#define FilterBankController_h

#include "FilterBank.h"
#include "../../../Controller.h"
#include "../../../io/input/AnalogInput.h"
#include "../../../modules/StereoPan.h"

class FilterBankController : public Controller {
    public:
        FilterBankController() {}
        virtual void init(float sampleRate);
        virtual void update();
        virtual void process(float **in, float **out, size_t size);

    private:
        AnalogInput gainInput1 = AnalogInput(A0, -5, 5, 0, 1);
        AnalogInput gainInput2 = AnalogInput(A1, -5, 5, 0, 1);
        AnalogInput gainInput3 = AnalogInput(A2, -5, 5, 0, 1);
        AnalogInput gainInput4 = AnalogInput(A3, -5, 5, 0, 1);
        AnalogInput gainInput5 = AnalogInput(A4, -5, 5, 0, 1);
        AnalogInput gainInput6 = AnalogInput(A5, -5, 5, 0, 1);
        AnalogInput gainInput7 = AnalogInput(A6, -5, 5, 0, 1);
        AnalogInput gainInput8 = AnalogInput(A7, -5, 5, 0, 1);
        AnalogInput gainInput9 = AnalogInput(A8, -5, 5, 0, 1);
        AnalogInput gainInput10 = AnalogInput(A9, -5, 5, 0, 1);

        float stereoMix = 0.2; // 0-0.5 TODO make this physical input

        FilterBank filterBank;
        StereoPan oddPan;
        StereoPan evenPan;

};

#endif
