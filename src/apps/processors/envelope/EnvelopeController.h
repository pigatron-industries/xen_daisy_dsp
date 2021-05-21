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
        LinearInput<> attackTimeInput = LinearInput<>(AnalogPin(A1), -5, 5, 0, 1);
        LinearInput<> decayTimeInput = LinearInput<>(AnalogPin(A2), -5, 5, 0, 1);
        AnalogGateInput<> gateInput = AnalogGateInput<>(AnalogPin(A5), 3);

        Envelope envelope;
};

#endif
