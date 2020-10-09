#include "AutocorrelationAnalyser.h"


void AutocorrelationAnalyser::init(float sampleRate) {
    this->sampleRate = sampleRate;
    bufferPosition = 0;
}

void AutocorrelationAnalyser::process(float in) {
    if(bufferPosition < AUTOCORRELATION_BUFFER_SIZE) {
        buffer[bufferPosition] = in;
        bufferPosition++;
    }
}

bool AutocorrelationAnalyser::calculate() {
    if(bufferPosition < AUTOCORRELATION_BUFFER_SIZE) {
        return false;
    } else {
        compute();
        bufferPosition = 0;
        return true;
    }
}

void AutocorrelationAnalyser::compute() {
    int peakDetectState = 0;
    int period = 0;
    float threshold = 0;
    float sum = 0;
    float sumOld = 0;

    for(int i = 0; i < AUTOCORRELATION_BUFFER_SIZE; i++) {

        // autocorrelation
        sumOld = sum;
        sum = 0;
        for(int j = 0; j < AUTOCORRELATION_BUFFER_SIZE-i; j++) {
            sum += buffer[j] * buffer[j+i];
        }

        // peak detection
        if(peakDetectState == 2 && (sum-sumOld) <= 0) {
            period = i;
            peakDetectState = 3;
        }
        if(peakDetectState == 1 && sum > threshold && (sum-sumOld) > 0) {
            peakDetectState = 2;
        }
        if(peakDetectState == 0) {
            threshold = sum * 0.5;
            peakDetectState = 1;
        }
    }

    if(peakDetectState == 3 && period > 3) {
        frequency = sampleRate/period;
    }
}

