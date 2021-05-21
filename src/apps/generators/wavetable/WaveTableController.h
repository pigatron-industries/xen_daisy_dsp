#ifndef WaveTableController_h
#define WaveTableController_h

#include "Controller.h"
#include "modules/wavetable/WaveTableOscillator.h"

class WaveTableController : public Controller {
    public:
        WaveTableController() {}
        virtual void firstInit(float sampleRate);
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        ExpInput<> pitchInput = ExpInput<>(AnalogPin(A0));
        LinearInput<> interpolationInput = LinearInput<>(AnalogPin(A1), -5, 5, 0, 3.1);

        WaveTableOscillator oscillator;
        WaveTable wavetable1;
        WaveTable wavetable2;
        WaveTable wavetable3;
        WaveTable wavetable4;
};

#endif
