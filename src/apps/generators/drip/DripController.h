#ifndef DripController_h
#define DripController_h

#include "Controller.h"
#include "modules/physical/Drip.h"
#include "io/input/AnalogInput.h"
#include "io/input/GateInput.h"

class DripController : public Controller {
    public:
        DripController() {}
        virtual void init(float sampleRate);
        virtual void update();
        virtual void process(float **in, float **out, size_t size);

    private:
        GateInput gateInput = GateInput(A5);

        bool trigger;
        pigatron::Drip drip;
};

#endif
