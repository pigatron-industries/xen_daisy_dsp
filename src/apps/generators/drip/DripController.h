#ifndef DripController_h
#define DripController_h

#include "Controller.h"
#include "modules/physical/Drip.h"

class DripController : public Controller {
    public:
        DripController() {}
        virtual void init(float sampleRate);
        virtual void update();
        virtual void process(float **in, float **out, size_t size);

    private:
        AnalogGateInput<AnalogInputPin> gateInput = AnalogGateInput<AnalogInputPin>(AnalogInputPin(A5), 3);

        bool trigger;
        pigatron::Drip drip;
};

#endif
