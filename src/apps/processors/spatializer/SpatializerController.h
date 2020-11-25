#ifndef SpatializerController_h
#define SpatializerController_h

#include "Spatializer.h"
#include "../../../Controller.h"
#include "../../../io/input/AnalogInput.h"

class SpatializerController : public Controller {
    public:
        SpatializerController() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        AnalogInput xInput = AnalogInput(A0, -5, 5, -10, 10);
        AnalogInput yInput = AnalogInput(A1, -5, 5, -10, 10);

        Spatializer spatializer;
};

#endif
