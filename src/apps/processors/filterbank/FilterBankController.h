#ifndef FilterBankController_h
#define FilterBankController_h

#include "FilterBank.h"
#include "Controller.h"
#include "modules/StereoPan.h"

class FilterBankController : public Controller {
    public:
        FilterBankController() {}
        virtual void init(float sampleRate);
        virtual void update();
        virtual void process(float **in, float **out, size_t size);

    private:
        LinearInput gainInput1 = LinearInput(A0, -5, 5, 0, 1);
        LinearInput gainInput2 = LinearInput(A1, -5, 5, 0, 1);
        LinearInput gainInput3 = LinearInput(A2, -5, 5, 0, 1);
        LinearInput gainInput4 = LinearInput(A3, -5, 5, 0, 1);
        LinearInput gainInput5 = LinearInput(A4, -5, 5, 0, 1);
        LinearInput gainInput6 = LinearInput(A5, -5, 5, 0, 1);
        LinearInput gainInput7 = LinearInput(A6, -5, 5, 0, 1);
        LinearInput gainInput8 = LinearInput(A7, -5, 5, 0, 1);
        LinearInput gainInput9 = LinearInput(A8, -5, 5, 0, 1);
        LinearInput gainInput10 = LinearInput(A9, -5, 5, 0, 1);
        LinearInput gainInput11 = LinearInput(A10, -5, 5, 0, 1);
        LinearInput gainInput12 = LinearInput(A11, -5, 5, 0, 1);

        float stereoMix = 0.2; // 0-0.5 TODO make this physical input

        FilterBank filterBank;
        StereoPan oddPan;
        StereoPan evenPan;

};

#endif
