#ifndef GlottisController_h
#define GlottisController_h

#include "DaisyDuino.h"
#include "Glottis.h"
#include "../../../Controller.h"
#include "../../../modules/BiquadFilter.h"
#include "../../../io/PitchInput.h"
#include "../../../io/AnalogInput.h"

class GlottisController : public Controller {
    public:
        GlottisController(Hardware& hardware);
        virtual void init(float sampleRate);
        virtual void update();
        virtual void process(float **in, float **out, size_t size);

    private:
        PitchInput pitchInput = PitchInput(A0, 110);
        AnalogInput tensenessInput = AnalogInput(A1, -5, 5, 0, 1);

        WhiteNoise whiteNoise;
        BiquadFilter aspirateFilter;
        Glottis glottis;
};

#endif