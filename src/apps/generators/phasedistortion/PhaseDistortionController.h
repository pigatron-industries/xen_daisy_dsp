#ifndef PhaseDistortionController_h
#define PhaseDistortionController_h

#include "Controller.h"
#include "modules/oscillators/PhaseDistortionOscillator.h"

class PhaseDistortionController : public Controller {
    public:
        PhaseDistortionController() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:

        ExpInput<> pitchInput = ExpInput<>(AnalogPin(A0));
        LinearInput<> x1Input = LinearInput<>(AnalogPin(A1), -5, 5, 0, 1);
        LinearInput<> y1Input = LinearInput<>(AnalogPin(A2), -5, 5, 0, 1);
        LinearInput<> phaseOffsetInput = LinearInput<>(AnalogPin(A3), -5, 5, 0, 1);
        LinearInput<> harmonicsInput = LinearInput<>(AnalogPin(A4), -5, 5, 0, 4);

        PhaseDistortionOscillator oscillator;
        WaveTable wavetable1;
        WaveTable wavetable2;
        WaveTable wavetable3;
        WaveTable wavetable4;
        WaveTable wavetable5;
};

#endif
