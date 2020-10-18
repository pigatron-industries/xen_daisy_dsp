#include "FFTAnalyser.h"


void FFTAnalyser::init(float sampleRate) {
    this->sampleRate = sampleRate;
    bufferPosition = 0;
    fft = arduinoFFT(real, imaginary, FFT_SAMPLES, sampleRate);
}

void FFTAnalyser::process(float in) {
    if(!bufferFull()) {
        real[bufferPosition] = in;
        bufferPosition++;
    }
}

bool FFTAnalyser::calculate() {
    if(!bufferFull()) {
        return false;
    } else {
        compute();
        bufferPosition = 0;
        return true;
    }
}

void FFTAnalyser::compute() {
    for(int i = 0; i < FFT_SAMPLES; i++) {
        imaginary[i] = 0;
    }
    fft.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    fft.Compute(FFT_FORWARD);
    fft.ComplexToMagnitude();
    frequency = fft.MajorPeak();
}
