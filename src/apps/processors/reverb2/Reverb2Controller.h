#ifndef Reverb2Controller_h
#define Reverb2Controller_h

#include "Controller.h"

#include "utility/DaisySP/daisysp.h"


class Reverb2Controller : public Controller {
    public:
        Reverb2Controller() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        LinearInput<> feedbackInput = LinearInput<>(AnalogPin(A0), -5, 5, 0, 1);
        ExpInput<> filterInput = ExpInput<>(AnalogPin(A1));
        CrossfadeInput<> dryWetMix = CrossfadeInput<>(AnalogPin(A2), -4.8, 4.8);

        daisysp::ReverbSc reverb;

        int sampleRate;
};

#endif
