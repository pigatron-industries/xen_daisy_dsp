#ifndef AdditiveOscillatorController_h
#define AdditiveOscillatorController_h

#include "Controller.h"
#include "OscillatorCluster.h"
#include "io/input/ExpInput.h"
#include "io/input/AnalogInput.h"
#define OSCILLATOR_COUNT 10

class ClusterController : public Controller {
    public:
        ClusterController() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        ExpInput frequencyInput = ExpInput(A0);

        // AdditiveOscillator oscillator;
        // Normalizer normalizer;
};

#endif
