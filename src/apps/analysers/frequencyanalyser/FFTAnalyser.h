#ifndef FFTAnalyser_h
#define FFTAnalyser_h

#include "arduinoFFT.h"

#define FFT_SAMPLES 1024

class FFTAnalyser {
    public:
        FFTAnalyser() {}
        void init(float sampleRate);
        void process(float in);

        bool calculate();
        bool bufferFull() { return bufferPosition == FFT_SAMPLES; }
        float getFrequency() { return frequency; }

    private:
        float sampleRate;
        arduinoFFT fft;

        int bufferPosition = 0;
        double real[FFT_SAMPLES];
        double imaginary[FFT_SAMPLES];

        float frequency = 0;

        void compute();

};

#endif