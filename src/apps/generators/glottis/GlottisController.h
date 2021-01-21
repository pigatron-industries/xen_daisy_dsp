#ifndef GlottisController_h
#define GlottisController_h

#include "DaisyDuino.h"
#include "Glottis.h"
#include "Vibrato.h"
#include "../../../Controller.h"
#include "../../../modules/filters/BiquadFilter.h"
#include "../../../io/input/ExpInput.h"
#include "../../../io/input/AnalogInput.h"

class GlottisController : public Controller {
    public:
        GlottisController() {}
        virtual void init(float sampleRate);
        virtual void update();
        virtual void process(float **in, float **out, size_t size);

    private:
        ExpInput pitchInput = ExpInput(A0);
        AnalogInput tensenessInput = AnalogInput(A1, -5, 5, 0, 1);
        AnalogInput vibratoAmountInput = AnalogInput(A2, -5, 5, 0, 1);
        AnalogInput noiseAmountInput = AnalogInput(A3, -5, 5, 0, 1);

        WhiteNoise whiteNoise;
        BiquadFilter aspirateFilter;
        Glottis glottis;
        Vibrato vibrato;
};

#endif