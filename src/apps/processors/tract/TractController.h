#ifndef TractController_h
#define TractController_h

#include <DaisyDSP.h>
#include "Controller.h"
#include "modules/filters/BiquadFilter.h"
#include "Tract.h"

class TractController : public Controller {
    public:
        TractController() {}
        virtual void init(float sampleRate);
        virtual void update();
        virtual void process(float **in, float **out, size_t size);

    private:
        Tract tract;
        WhiteNoise whiteNoise;
        BiquadFilter fricativeFilter;

        LinearInput<> tongueX = LinearInput<>(HW.A0, -5, 5, 0, 1);
        LinearInput<> tongueY = LinearInput<>(HW.A1, -5, 5, 0, 1);
        LinearInput<> constrictionX = LinearInput<>(HW.A2, -5, 5, 0, 1);
        LinearInput<> constrictionY = LinearInput<>(HW.A3, -5, 5, 0.3, 2);

        float fricativeIntensity = 0.0;

};

#endif
