#ifndef AutocorrelationAnalyser_h
#define AutocorrelationAnalyser_h

#include "arduinoFFT.h"

#define AUTOCORRELATION_BUFFER_SIZE 1024

class AutocorrelationAnalyser {
    public:
        AutocorrelationAnalyser() {}
        void init(float sampleRate);
        void process(float in);
    
        bool calculate();
        float getFrequency() { return frequency; }

    private:
        float sampleRate;

        int bufferPosition = 0;
        float buffer[AUTOCORRELATION_BUFFER_SIZE];

        float frequency = 0;

        void compute();

};

#endif