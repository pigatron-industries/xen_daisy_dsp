#ifndef GlitchLoopController_h
#define GlitchLoopController_h

#include "Controller.h"
#include "modules/delays/SampleBuffer.h"

enum GlitchState {
    GLITCH_OFF,
    GLITCH_WRITE_DELAY,
    GLITCH_WRITE,
    GLITCH_READ_DELAY,
    GLITCH_READ
};

class GlitchLoopController : public Controller {
    public:
        static constexpr float MAX_DELAY = 0.5;

        GlitchLoopController() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        ExpInput<> sampleTimeInput = ExpInput<>(AnalogPin(A0), 0.05);
        LinearInput<> writeDelayStartInput = LinearInput<>(AnalogPin(A1), -5, 5, 0, MAX_DELAY);
        LinearInput<> readDelayStartInput = LinearInput<>(AnalogPin(A2), -5, 5, 0, MAX_DELAY);
        LinearInput<> dryGainInput = LinearInput<>(AnalogPin(A3), -5, 5, 0, 1);
        AnalogGateInput<> gateInput = AnalogGateInput<>(AnalogPin(A5), 3);
        
        SampleBuffer buffer1;
        SampleBuffer buffer2;

        GlitchState state;

        float dryGain;

        int writeDelaySamples;
        int writeDelayCounter;
        int readDelaySamples;
        int readDelayCounter;
        int sampleRate;
};

#endif
