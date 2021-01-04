#ifndef AdditiveOscillatorController_h
#define AdditiveOscillatorController_h

#include "../../../Controller.h"
#include "../../../io/input/ExpInput.h"
#include "../../../io/input/AnalogInput.h"
#include "AdditiveOscillator.h"
#include "Normalizer.h"

#define OSCILLATOR_COUNT 10

class AdditiveOscillatorController : public Controller {
    public:
        AdditiveOscillatorController() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        AnalogInput amplitudeInputs[OSCILLATOR_COUNT] = {
            AnalogInput(A0, -5, 5, 0, 1),
            AnalogInput(A1, -5, 5, 0, 1),
            AnalogInput(A2, -5, 5, 0, 1),
            AnalogInput(A3, -5, 5, 0, 1),
            AnalogInput(A4, -5, 5, 0, 1),
            AnalogInput(A5, -5, 5, 0, 1),
            AnalogInput(A6, -5, 5, 0, 1),
            AnalogInput(A7, -5, 5, 0, 1),
            AnalogInput(A8, -5, 5, 0, 1),
            AnalogInput(A9, -5, 5, 0, 1),
        };
        ExpInput frequencyInput = ExpInput(A11);

        AdditiveOscillator oscillator;
        Normalizer normalizer;
};

#endif
