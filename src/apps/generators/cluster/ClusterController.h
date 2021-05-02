#ifndef ClusterController_h
#define ClusterController_h

#include "Controller.h"
#include "OscillatorBank.h"
#include "io/input/ExpInput.h"
#include "io/input/AnalogInput.h"

class ClusterController : public Controller {
    public:
        ClusterController() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        ExpInput frequencyInput = ExpInput(A0);
        AnalogInput interval1Input = AnalogInput(A1, -5, 5, 0, 1);

        pigatron::OscillatorBank oscillatorBank;
};

#endif
