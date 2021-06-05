#ifndef GlitchAliasController_h
#define GlitchAliasController_h

#include "Controller.h"
#include "modules/oscillators/Oscillator.h"

class GlitchAliasController : public Controller {
    public:
        GlitchAliasController() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        LinearInput<> pitchInput = LinearInput<>(AnalogInputPin(A0), -5, 5, 2000, 46000);
        LinearInput<> fineInput = LinearInput<>(AnalogInputPin(A1), -5, 5, -500, 500);
        LinearInput<> mixInput = LinearInput<>(AnalogInputPin(A2), -5, 5, 0, 1);

        pigatron::Oscillator square;
        pigatron::Oscillator saw;

        float mix;
};

#endif
