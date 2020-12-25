#ifndef OscillatorController_h
#define OscillatorController_h

#include "../../../Controller.h"
#include "../../../io/input/ExpInput.h"

class OscillatorController : public Controller {
    public:
        OscillatorController() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        ExpInput pitchInput = ExpInput(A0);

        Oscillator oscillator;
};

#endif
