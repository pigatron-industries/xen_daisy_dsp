#ifndef GlitchAliasController_h
#define GlitchAliasController_h

#include "Controller.h"
#include "io/input/ExpInput.h"
#include "io/input/AnalogInput.h"

class GlitchAliasController : public Controller {
    public:
        GlitchAliasController() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        AnalogInput pitchInput = AnalogInput(A0, -5, 5, 2000, 46000);
        AnalogInput fineInput = AnalogInput(A1, -5, 5, -500, 500);
        AnalogInput mixInput = AnalogInput(A2, -5, 5, 0, 1);

        Oscillator square;
        Oscillator saw;

        float mix;
};

#endif
