#ifndef OscillatorController_h
#define OscillatorController_h

#include "../../../Controller.h"
#include "../../../io/input/PitchInput.h"

class OscillatorController : public Controller {
    public:
        OscillatorController() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        PitchInput pitchInput = PitchInput(A0, 110);

        Oscillator oscillator;
};

#endif
