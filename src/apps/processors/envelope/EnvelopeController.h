#ifndef EnvelopeController_h
#define EnvelopeController_h

#include "Controller.h"
#include "modules/Envelope.h"

class EnvelopeController : public Controller {
    public:
        EnvelopeController() {}
        virtual void init(float sampleRate);
        virtual void update();
        virtual void process(float **in, float **out, size_t size);

    private:
        LinearInput<> attackTimeInput = LinearInput<>(HW.A1, -5, 5, 0, 1);
        LinearInput<> decayTimeInput = LinearInput<>(HW.A2, -5, 5, 0, 1);
        AnalogGateInput<> gateInput = AnalogGateInput<>(HW.A5, 3);

        deprecated::Envelope envelope;
};

#endif
