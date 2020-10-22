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
        AnalogInput panInput = AnalogInput(A0, -5, 5, -1, 1);

        Spatializer spatializer;
};

#endif
