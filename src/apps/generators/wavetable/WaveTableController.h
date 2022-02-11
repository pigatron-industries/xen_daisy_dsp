#ifndef WaveTableController_h
#define WaveTableController_h

#include "Controller.h"
#include "modules/wavetable/WaveTableOscillator.h"
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

        WaveTable<10, 128> wavetable1;
        WaveOscillator<WaveTable<10, 128>&> oscillator = WaveOscillator<WaveTable<10, 128>&>(wavetable1);

        //WaveTableOscillator oscillator;
        // deprecated::WaveTable wavetable1;
        // deprecated::WaveTable wavetable2;
        // deprecated::WaveTable wavetable3;
        // deprecated::WaveTable wavetable4;
};

#endif
