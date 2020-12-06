#ifndef WaveTableController_h
#define WaveTableController_h

#include "../../../Controller.h"
#include "../../../io/input/PitchInput.h"
#include "../../../io/input/AnalogInput.h"
#include "WaveTableOscillator.h"
#include "../../../modules/filters/BiquadFilter.h"

class WaveTableController : public Controller {
    public:
        WaveTableController() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        PitchInput pitchInput = PitchInput(A0);
        AnalogInput interpolationInput = AnalogInput(A1, -5, 5, 0, 1);

        WaveTableOscillator oscillator;
        WaveTable wavetable1;
        WaveTable wavetable2;
};

#endif
