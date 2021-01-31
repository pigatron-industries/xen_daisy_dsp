#ifndef PhaseDistortionController_h
#define PhaseDistortionController_h

#include "../../../Controller.h"
#include "../../../io/input/AnalogInput.h"
#include "../../../io/input/ExpInput.h"
#include "../../../modules/distortion/PhaseDistortion.h"
#include "../../../modules/distortion/PowerFunction.h"

class PhaseDistortionController : public Controller {
    public:
        PhaseDistortionController() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        ExpInput pitchInput = ExpInput(A0);
        ExpInput powerInput = ExpInput(A1, 1);
        AnalogInput phaseOffsetInput = AnalogInput(A2, -5, 5, 0, 1);

        PhaseDistortion phaseDistortion;

        PowerFunction powerFunction;
};

#endif
