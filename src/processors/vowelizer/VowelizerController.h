#ifndef VowelizerController_h
#define VowelizerController_h

#include "../Controller.h"
#include "Vowelizer.h"
#include "../../io/AnalogInput.h"

class VowelizerController : public Controller {
    public:
        VowelizerController();
        void init(float sampleRate);
        void update();
        void process(float **in, float **out, size_t size);

    private:
        Vowelizer vowelizer;
        AnalogInput rangeInput;
        AnalogInput vowelInput;
        AnalogInput pitchInput;

};

#endif