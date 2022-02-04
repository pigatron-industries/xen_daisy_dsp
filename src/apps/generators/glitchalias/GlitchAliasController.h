#ifndef GlitchAliasController_h
#define GlitchAliasController_h

#include "Controller.h"
#include <eurorack_dsp.h>

using namespace eurorack;

class GlitchAliasController : public Controller {
    public:
        GlitchAliasController() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        LinearInput<> pitchInput = LinearInput<>(HW.A0, -5, 5, 2000, 46000);
        LinearInput<> fineInput = LinearInput<>(HW.A1, -5, 5, -500, 500);
        LinearInput<> mixInput = LinearInput<>(HW.A2, -5, 5, 0, 1);

        WaveOscillator<Pulse> square;
        WaveOscillator<Saw> saw;

        float mix;
};

#endif
