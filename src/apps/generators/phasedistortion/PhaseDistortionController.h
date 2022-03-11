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

        typedef WaveTable<10, 128> WaveTableT;
        typedef WaveInterpolator<WaveTableT&, WaveTableT&, WaveTableT&, WaveTableT&, WaveTableT&> WaveInterpolatorT;
        typedef WaveInterpolator<WaveInterpolatorT&, WaveInterpolatorT&, WaveInterpolatorT&> Interpolator2T;

        WaveTableT wavetableSine1;
        WaveTableT wavetableSine2;
        WaveTableT wavetableSine3;
        WaveTableT wavetableSine4;
        WaveTableT wavetableSine5;
        WaveTableT wavetableRamp1;
        WaveTableT wavetableRamp2;
        WaveTableT wavetableRamp3;
        WaveTableT wavetableRamp4;
        WaveTableT wavetableRamp5;
        WaveTableT wavetableSquare1;
        WaveTableT wavetableSquare2;
        WaveTableT wavetableSquare3;
        WaveTableT wavetableSquare4;
        WaveTableT wavetableSquare5;

        WaveInterpolatorT sineInterpolator = WaveInterpolatorT(wavetableSine1, wavetableSine2, wavetableSine3, wavetableSine4, wavetableSine5);
        WaveInterpolatorT rampInterpolator = WaveInterpolatorT(wavetableRamp1, wavetableRamp2, wavetableRamp3, wavetableRamp4, wavetableRamp5);
        WaveInterpolatorT squareInterpolator = WaveInterpolatorT(wavetableSquare1, wavetableSquare2, wavetableSquare3, wavetableSquare4, wavetableSquare5);
        Interpolator2T interpolator = Interpolator2T(sineInterpolator, rampInterpolator, squareInterpolator);

        TwoLineFunction distortionFunction;

        PhaseDistortionOscillator<Interpolator2T&, TwoLineFunction&> oscillator = PhaseDistortionOscillator<Interpolator2T&, TwoLineFunction&>(interpolator, distortionFunction);
};

#endif
