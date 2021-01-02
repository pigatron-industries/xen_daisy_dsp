#ifndef WaveTableController_h
#define WaveTableController_h

#include "../../../Controller.h"
#include "../../../io/input/ExpInput.h"
#include "../../../io/input/AnalogInput.h"
#include "../../../modules/wavetable/WaveTableOscillator.h"

class WaveTableController : public Controller {
    public:
        WaveTableController() {}
        virtual void firstInit(float sampleRate);
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        ExpInput pitchInput = ExpInput(A0);
        AnalogInput interpolationInput = AnalogInput(A1, -5, 5, 0, 3);

        WaveTableOscillator oscillator;
        WaveTable wavetable1;
        WaveTable wavetable2;
        WaveTable wavetable3;
        WaveTable wavetable4;
};

#endif
