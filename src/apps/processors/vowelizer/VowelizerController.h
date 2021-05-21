#ifndef VowelizerController_h
#define VowelizerController_h

#include "Controller.h"
#include "Vowelizer.h"

class VowelizerController : public Controller {
    public:
        VowelizerController() {}
        virtual void init(float sampleRate);
        virtual void update();
        virtual void process(float **in, float **out, size_t size);

    private:
        Vowelizer vowelizer;
        LinearInput<> rangeInput = LinearInput<>(AnalogInputPin(A0), -5, 5, 0, 5);
        LinearInput<> vowelInput = LinearInput<>(AnalogInputPin(A1), -5, 5, 0, 5);
        LinearInput<> pitchInput = LinearInput<>(AnalogInputPin(A2), -5, 5, 1, 2);
        LinearInput<> resonanceInput = LinearInput<>(AnalogInputPin(A3), -5, 5, 0, 1);

};

#endif