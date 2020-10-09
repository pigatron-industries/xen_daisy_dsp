#ifndef FrequencyController_h
#define FrequencyController_h

#include "FFTAnalyser.h"
#include "AutocorrelationAnalyser.h"
#include "../../../Controller.h"
#include "../../../io/PitchOutput.h"

class FrequencyController : public Controller {
    public:

        enum AnalyserType {
            FFT,
            AUTOCORRELATION
        };

        FrequencyController() {}
        virtual void init(float sampleRate);
        virtual void update();
        virtual void updateDisplay();
        virtual void event(UIEvent event, int itemIndex);
        virtual void process(float **in, float **out, size_t size);

    private:
        PitchOutput pitchOutput = PitchOutput(23);

        AnalyserType type = FFT;

        FFTAnalyser fftAnalyser;
        AutocorrelationAnalyser autocorrelationAnalyser;

        String getTypeText();

};

#endif