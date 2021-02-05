#ifndef EnvelopeController_h
#define EnvelopeController_h

#include "../../../Controller.h"
#include "../../../modules/Envelope.h"
#include "../../../io/input/AnalogInput.h"
#include "../../../io/input/GateInput.h"

class EnvelopeController : public Controller {
    public:
        EnvelopeController() {}
        virtual void init(float sampleRate);
        virtual void update();
        virtual void process(float **in, float **out, size_t size);

    private:
        AnalogInput attackTimeInput = AnalogInput(A1, -5, 5, 0, 1);
        AnalogInput decayTimeInput = AnalogInput(A2, -5, 5, 0, 1);
        GateInput gateInput = GateInput(A5);

        Envelope envelope;
};

#endif
