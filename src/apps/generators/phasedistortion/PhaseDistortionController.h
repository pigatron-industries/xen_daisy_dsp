#ifndef PhaseDistortionController_h
#define PhaseDistortionController_h

#include "Controller.h"
#include <eurorack_dsp.h>

using namespace eurorack;


class PhaseDistortionController : public Controller {
    public:
        PhaseDistortionController() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:

        ExpInput<> pitchInput = ExpInput<>(HW.A0);
        LinearInput<> x1Input = LinearInput<>(HW.A1, -5, 5, 0, 1);
        LinearInput<> y1Input = LinearInput<>(HW.A2, -5, 5, 0, 1);
        LinearInput<> waveInput = LinearInput<>(HW.A3, -5, 5, 0, 2);
        LinearInput<> harmonicsInput = LinearInput<>(HW.A4, -5, 5, 0, 4);

        typedef WaveInterpolator2D<WaveTable<10, 128>, 5, 3> WaveInterpolatorT;

        WaveInterpolatorT interpolator;

        TwoLineFunction distortionFunction;

        PhaseDistortionOscillator<WaveInterpolatorT&, TwoLineFunction&> oscillator = PhaseDistortionOscillator<WaveInterpolatorT&, TwoLineFunction&>(interpolator, distortionFunction);
};

#endif
