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
        LinearInput<> gainInput1 = LinearInput<>(AnalogInputPin(A0), -5, 5, 0, 1);
        LinearInput<> gainInput2 = LinearInput<>(AnalogInputPin(A1), -5, 5, 0, 1);
        LinearInput<> gainInput3 = LinearInput<>(AnalogInputPin(A2), -5, 5, 0, 1);
        LinearInput<> gainInput4 = LinearInput<>(AnalogInputPin(A3), -5, 5, 0, 1);
        LinearInput<> gainInput5 = LinearInput<>(AnalogInputPin(A4), -5, 5, 0, 1);
        LinearInput<> gainInput6 = LinearInput<>(AnalogInputPin(A5), -5, 5, 0, 1);
        LinearInput<> gainInput7 = LinearInput<>(AnalogInputPin(A6), -5, 5, 0, 1);
        LinearInput<> gainInput8 = LinearInput<>(AnalogInputPin(A7), -5, 5, 0, 1);
        LinearInput<> gainInput9 = LinearInput<>(AnalogInputPin(A8), -5, 5, 0, 1);
        LinearInput<> gainInput10 = LinearInput<>(AnalogInputPin(A9), -5, 5, 0, 1);
        LinearInput<> gainInput11 = LinearInput<>(AnalogInputPin(A10), -5, 5, 0, 1);
        LinearInput<> gainInput12 = LinearInput<>(AnalogInputPin(A11), -5, 5, 0, 1);

        float stereoMix = 0.2; // 0-0.5 TODO make this physical input

        FilterBank filterBank;
        StereoPan oddPan;
        StereoPan evenPan;

};

#endif
