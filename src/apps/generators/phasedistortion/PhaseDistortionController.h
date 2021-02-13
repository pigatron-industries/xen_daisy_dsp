#ifndef PhaseDistortionController_h
#define PhaseDistortionController_h

#include "Controller.h"
#include "io/input/AnalogInput.h"
#include "io/input/ExpInput.h"
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
            AnalogInput x1Input = AnalogInput(A1, -5, 5, 0, 1);
            AnalogInput y1Input = AnalogInput(A2, -5, 5, 0, 1);
            AnalogInput phaseOffsetInput = AnalogInput(A3, -5, 5, 0, 1);
            AnalogInput harmonicsInput = AnalogInput(A4, -5, 5, 0, 4);
        #else
            ExpInput pitchInput = ExpInput(A0);
            AnalogInput x1Input = AnalogInput(A2, -5, 5, 0, 0.25);
            AnalogInput y1Input = AnalogInput(A3, -5, 5, 0, 1);
            AnalogInput x2Input = AnalogInput(A4, -5, 5, 0.25, 0.5);
            AnalogInput y2Input = AnalogInput(A5, -5, 5, 0, 1);
            AnalogInput x3Input = AnalogInput(A6, -5, 5, 0.5, 0.75);
            AnalogInput y3Input = AnalogInput(A7, -5, 5, 0, 1);
            AnalogInput x4Input = AnalogInput(A8, -5, 5, 0.75, 1);
            AnalogInput y4Input = AnalogInput(A9, -5, 5, 0, 1);
            AnalogInput phaseOffsetInput = AnalogInput(A10, -5, 5, 0, 1);
            AnalogInput harmonicsInput = AnalogInput(A11, -5, 5, 0, 4);
        #endif

        PhaseDistortionOscillator oscillator;
        WaveTable wavetable1;
        WaveTable wavetable2;
        WaveTable wavetable3;
        WaveTable wavetable4;
        WaveTable wavetable5;
};

#endif
