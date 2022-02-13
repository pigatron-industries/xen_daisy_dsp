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
        LinearInput<> phaseOffsetInput = LinearInput<>(HW.A3, -5, 5, 0, 1);
        LinearInput<> harmonicsInput = LinearInput<>(HW.A4, -5, 5, 0, 4);

        typedef WaveTable<10, 128> WaveTableT;
        typedef WaveInterpolator<WaveTableT&, WaveTableT&, WaveTableT&, WaveTableT&, WaveTableT&> WaveInterpolatorT;

        WaveTableT wavetable1;
        WaveTableT wavetable2;
        WaveTableT wavetable3;
        WaveTableT wavetable4;
        WaveTableT wavetable5;

        TwoLineFunction distortionFunction;

        WaveInterpolatorT interpolator = WaveInterpolatorT(wavetable1, wavetable2, wavetable3, wavetable4, wavetable5);
        PhaseDistortionOscillator<WaveInterpolatorT&, TwoLineFunction&> oscillator = PhaseDistortionOscillator<WaveInterpolatorT&, TwoLineFunction&>(interpolator, distortionFunction);
};

#endif
