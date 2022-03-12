#ifndef WaveTableController_h
#define WaveTableController_h

#include "Controller.h"
#include <eurorack_dsp.h>

using namespace eurorack;

class WaveTableController : public Controller {
    public:
        WaveTableController() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        ExpInput<> pitchInput = ExpInput<>(HW.A0);
        LinearInput<> interpolationInput = LinearInput<>(HW.A1, -5, 5, 0, 3.1);

        typedef WaveTable<10, 128> WaveTableT;
        typedef WaveInterpolator<WaveTableT&, WaveTableT&, WaveTableT&, WaveTableT&> WaveInterpolatorT;

        WaveTableT wavetable1;
        WaveTableT wavetable2;
        WaveTableT wavetable3;
        WaveTableT wavetable4;

        WaveInterpolatorT interpolator = WaveInterpolatorT(wavetable1, wavetable2, wavetable3, wavetable4);
        WaveOscillator<WaveInterpolatorT&> oscillator = WaveOscillator<WaveInterpolatorT&>(interpolator);
};

#endif
