#ifndef VowelizerController_h
#define VowelizerController_h

#include "../../../Controller.h"
#include "Vowelizer.h"
#include "../../../io/AnalogInput.h"

class VowelizerController : public Controller {
    public:
        VowelizerController() {}
        virtual void init(float sampleRate);
        virtual void update();
        virtual void process(float **in, float **out, size_t size);
        virtual void render();

    private:
        Vowelizer vowelizer;
        AnalogInput rangeInput = AnalogInput(A0, -5, 5, 0, 5);
        AnalogInput vowelInput = AnalogInput(A1, -5, 5, 0, 5);
        AnalogInput pitchInput = AnalogInput(A2, -5, 5, 1, 2);
        AnalogInput resonanceInput = AnalogInput(A3, -5, 5, 0, 1);

};

#endif