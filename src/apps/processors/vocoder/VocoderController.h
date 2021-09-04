#ifndef VocoderController_h
#define VocoderController_h

#include "Vocoder.h"
#include "Controller.h"
#include "modules/StereoPan.h"

/**
 * Vocoder
 * 
 * TODO:
 * * Auto reduce number of bands when frequency of higher bands goes too high
 * * Option to modulate pitch interval around centre frequency instead of start frequency
 * * Option to use discrete pitch intervals
 * * Seperate carrier and modulator band pitch intervals with option to invert them.
 * * Stereo effect by spliiting different bands to different channels
 */

class VocoderController : public Controller {
    public:
        VocoderController() {}
        virtual void init(float sampleRate);
        virtual void update();
        virtual void updateDisplay();
        virtual void event(UIEvent event, int itemIndex);
        virtual void process(float **in, float **out, size_t size);

    private:
        LinearInput<> resonanceInput = LinearInput<>(HW.A0, -5, 5, 0, 1);
        ExpInput<> centreFrequencyInput = ExpInput<>(HW.A1);
        LinearInput<> pitchIntervalInput = LinearInput<>(HW.A2, -5, 5, 0.1, 1.0);
        LinearInput<> stereoMixInput = LinearInput<>(HW.A3, -5, 5, 0, 1);

        int bands = 10;

        Vocoder vocoder;
        StereoPan oddPan;
        StereoPan evenPan;
};

#endif
