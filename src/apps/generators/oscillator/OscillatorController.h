#ifndef OscillatorController_h
#define OscillatorController_h

#include <eurorack_dsp.h>
#include "Controller.h"

using namespace eurorack;

class OscillatorController : public Controller {
    public:
        OscillatorController() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        ExpInput<> pitchInput = ExpInput<>(HW.A0);
        LinearInput<> waveInput = LinearInput<>(HW.A1, -5, 5, 0, 5);

        WaveSelector<Sine, Triangle, Saw, Pulse> waveSelector;
        WaveOscillator<WaveSelector<Sine, Triangle, Saw, Pulse>&> oscillator = WaveOscillator<WaveSelector<Sine, Triangle, Saw, Pulse>&>(waveSelector);
};

#endif
