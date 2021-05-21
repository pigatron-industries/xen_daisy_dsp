#ifndef AdditiveOscillatorController_h
#define AdditiveOscillatorController_h

#include "Controller.h"
#include "AdditiveOscillator.h"
#include "modules/Normalizer.h"

#define OSCILLATOR_COUNT 10

class AdditiveOscillatorController : public Controller {
    public:
        AdditiveOscillatorController() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        LinearInput<> amplitudeInputs[OSCILLATOR_COUNT] = {
            LinearInput<>(AnalogPin(A0), -5, 5, 0, 1),
            LinearInput<>(AnalogPin(A1), -5, 5, 0, 1),
            LinearInput<>(AnalogPin(A2), -5, 5, 0, 1),
            LinearInput<>(AnalogPin(A3), -5, 5, 0, 1),
            LinearInput<>(AnalogPin(A4), -5, 5, 0, 1),
            LinearInput<>(AnalogPin(A5), -5, 5, 0, 1),
            LinearInput<>(AnalogPin(A6), -5, 5, 0, 1),
            LinearInput<>(AnalogPin(A7), -5, 5, 0, 1),
            LinearInput<>(AnalogPin(A8), -5, 5, 0, 1),
            LinearInput<>(AnalogPin(A9), -5, 5, 0, 1),
        };
        ExpInput<> frequencyInput = ExpInput<>(AnalogPin(A11));

        AdditiveOscillator oscillator;
        Normalizer normalizer;
};

#endif
