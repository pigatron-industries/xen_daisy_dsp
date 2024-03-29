#ifndef ClusterController_h
#define ClusterController_h

#include "Controller.h"
#include "modules/oscillators/OscillatorBank.h"

class ClusterController : public Controller {
    public:
        ClusterController() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        ExpInput<> centreFrequencyInput = ExpInput<>(HW.A0);
        LinearInput<> intervalInput = LinearInput<>(HW.A1, -5, 5, 0, 1);
        LinearInput<> offsetIntervalInput = LinearInput<>(HW.A2, -5, 5, 0, 1);

        pigatron::OscillatorBank oscillatorBank;
};

#endif
