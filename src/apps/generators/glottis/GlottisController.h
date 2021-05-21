#ifndef GlottisController_h
#define GlottisController_h

#include <utility/DaisySP/daisysp.h>
#include "Glottis.h"
#include "Vibrato.h"
#include "Controller.h"
#include "modules/filters/BiquadFilter.h"

class GlottisController : public Controller {
    public:
        GlottisController() {}
        virtual void init(float sampleRate);
        virtual void update();
        virtual void process(float **in, float **out, size_t size);

    private:
        ExpInput pitchInput = ExpInput(A0);
        LinearInput tensenessInput = LinearInput(A1, -5, 5, 0, 1);
        LinearInput vibratoAmountInput = LinearInput(A2, -5, 5, 0, 1);
        LinearInput noiseAmountInput = LinearInput(A3, -5, 5, 0, 1);

        daisysp::WhiteNoise whiteNoise;
        BiquadFilter aspirateFilter;
        Glottis glottis;
        Vibrato vibrato;
};

#endif