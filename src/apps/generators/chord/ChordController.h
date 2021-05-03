#ifndef ChordController_h
#define ChordController_h

#include "Controller.h"
#include "modules/oscillators/OscillatorBank.h"
#include "io/input/ExpInput.h"
#include "io/input/AnalogInput.h"

class ChordController : public Controller {
    public:
        ChordController() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        ExpInput frequencyInput = ExpInput(A0);
        AnalogInput chordInput = AnalogInput(A1, -5, 5, 0, 1);

        pigatron::OscillatorBank oscillatorBank;
};

#endif
