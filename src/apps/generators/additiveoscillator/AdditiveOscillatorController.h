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
            LinearInput<>(AnalogInputPin(A0), -5, 5, 0, 1),
            LinearInput<>(AnalogInputPin(A1), -5, 5, 0, 1),
            LinearInput<>(AnalogInputPin(A2), -5, 5, 0, 1),
            LinearInput<>(AnalogInputPin(A3), -5, 5, 0, 1),
            LinearInput<>(AnalogInputPin(A4), -5, 5, 0, 1),
            LinearInput<>(AnalogInputPin(A5), -5, 5, 0, 1),
            LinearInput<>(AnalogInputPin(A6), -5, 5, 0, 1),
            LinearInput<>(AnalogInputPin(A7), -5, 5, 0, 1),
            LinearInput<>(AnalogInputPin(A8), -5, 5, 0, 1),
            LinearInput<>(AnalogInputPin(A9), -5, 5, 0, 1),
        };
        ExpInput<> frequencyInput = ExpInput<>(AnalogInputPin(A11));

        AdditiveOscillator oscillator;
        Normalizer normalizer;
};

#endif
