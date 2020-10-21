#ifndef VocoderController_h
#define VocoderController_h

#include "Vocoder.h"
#include "../../../Controller.h"
#include "../../../io/input/AnalogInput.h"
#include "../../../modules/StereoPan.h"

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
        virtual void process(float **in, float **out, size_t size);

    private:
        AnalogInput resonanceInput = AnalogInput(A0, -5, 5, 0, 1);
        AnalogInput frequencyBaseInput = AnalogInput(A1, -5, 5, 55.0, 220.0);
        AnalogInput pitchIntervalInput = AnalogInput(A2, -5, 5, 0.25, 1.0);
        AnalogInput bandsInput = AnalogInput(A3, -5, 5, 1, 20.5); 

        float stereoMix = 0.2; // 0-0.5 TODO make this physical input

        Vocoder vocoder;
        StereoPan oddPan;
        StereoPan evenPan;
};

#endif
