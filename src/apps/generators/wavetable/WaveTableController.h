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

        typedef WaveArrayInterpolator<WaveTable<10, 128>, 4> WaveInterpolatorT;
        WaveInterpolatorT interpolator;
        WaveOscillator<WaveInterpolatorT&> oscillator = WaveOscillator<WaveInterpolatorT&>(interpolator);
};

#endif
