#include "FrequencyController.h"
#include "../../../util/Profiler.h"

#define LEFT 0
#define RIGHT 1

#define FIELD_TYPE 1
#define FIELD_FREQ 2


void FrequencyController::init(float sampleRate) {
    autocorrelationAnalyser.init(sampleRate);
    fftAnalyser.init(sampleRate);

    displayPage.initTitle("Frequency Analyser", "FREQ");
    displayPage.initField(FIELD_TYPE, getTypeText(), true);
    displayPage.initField(FIELD_FREQ, false);
}

void FrequencyController::update() {
    switch(type) {
        case AnalyserType::FFT:
            if(fftAnalyser.bufferFull()) {
                //PROFILE_START
                fftAnalyser.calculate();
                //PROFILE_END
                pitchOutput.setFrequency(fftAnalyser.getFrequency());
            }
            break;
        case AnalyserType::AUTOCORRELATION:
            if(autocorrelationAnalyser.bufferFull()) {
                //PROFILE_START
                autocorrelationAnalyser.calculate();
                //PROFILE_END
                pitchOutput.setFrequency(autocorrelationAnalyser.getFrequency());
            }
            break;
    }
}

void FrequencyController::updateDisplay() {
    switch(type) {
        case AnalyserType::FFT:
            displayPage.setText(FIELD_FREQ, String(fftAnalyser.getFrequency(), 2));
            break;
        case AnalyserType::AUTOCORRELATION:
            displayPage.setText(FIELD_FREQ, String(autocorrelationAnalyser.getFrequency(), 2));
            break;
    }
}

void FrequencyController::event(UIEvent event, int itemIndex) {
    if(itemIndex == FIELD_TYPE) {
        if(event == UIEvent::EVENT_CLOCKWISE) {
            type = static_cast<AnalyserType>((type + 1)%(AnalyserType::AUTOCORRELATION + 1));
            displayPage.setText(FIELD_TYPE, getTypeText());
        } else if (event == UIEvent::EVENT_COUNTERCLOCKWISE) {
            type = static_cast<AnalyserType>(type > 0 ? type - 1 : AnalyserType::AUTOCORRELATION);
            displayPage.setText(FIELD_TYPE, getTypeText());
        }
    }
}

void FrequencyController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        float sample = in[LEFT][i] < 0.01 && in[LEFT][i] > -0.01 ? 0 : in[LEFT][i]; //noise gate

        switch(type) {
            case AnalyserType::FFT:
                fftAnalyser.process(in[LEFT][i]);
                break;
            case AnalyserType::AUTOCORRELATION:
                autocorrelationAnalyser.process(in[LEFT][i]);
                break;
        }

        out[LEFT][i] = in[LEFT][i];
    }
}

String FrequencyController::getTypeText() {
    switch(type) {
        case AnalyserType::FFT:
            return "Fast Fourier Transform";
            break;
        case AnalyserType::AUTOCORRELATION:
            return "Autocorrelation";
            break;
    }
}