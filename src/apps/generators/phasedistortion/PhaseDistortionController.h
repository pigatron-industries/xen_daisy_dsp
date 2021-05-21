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

        #if defined(XEN_CV6)
            ExpInput pitchInput = ExpInput(A0);
            LinearInput x1Input = LinearInput(A1, -5, 5, 0, 1);
            LinearInput y1Input = LinearInput(A2, -5, 5, 0, 1);
            LinearInput phaseOffsetInput = LinearInput(A3, -5, 5, 0, 1);
            LinearInput harmonicsInput = LinearInput(A4, -5, 5, 0, 4);
        #else
            ExpInput pitchInput = ExpInput(A0);
            LinearInput x1Input = LinearInput(A2, -5, 5, 0, 0.25);
            LinearInput y1Input = LinearInput(A3, -5, 5, 0, 1);
            LinearInput x2Input = LinearInput(A4, -5, 5, 0.25, 0.5);
            LinearInput y2Input = LinearInput(A5, -5, 5, 0, 1);
            LinearInput x3Input = LinearInput(A6, -5, 5, 0.5, 0.75);
            LinearInput y3Input = LinearInput(A7, -5, 5, 0, 1);
            LinearInput x4Input = LinearInput(A8, -5, 5, 0.75, 1);
            LinearInput y4Input = LinearInput(A9, -5, 5, 0, 1);
            LinearInput phaseOffsetInput = LinearInput(A10, -5, 5, 0, 1);
            LinearInput harmonicsInput = LinearInput(A11, -5, 5, 0, 4);
        #endif

        PhaseDistortionOscillator oscillator;
        WaveTable wavetable1;
        WaveTable wavetable2;
        WaveTable wavetable3;
        WaveTable wavetable4;
        WaveTable wavetable5;
};

#endif
