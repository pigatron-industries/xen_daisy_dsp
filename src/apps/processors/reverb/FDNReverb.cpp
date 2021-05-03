#include "FDNReverb.h"
#include "math.h"

void FDNReverb::init(float sampleRate) {
    this->sampleRate = sampleRate;
    this->sampleTime = 1 / sampleRate;
    this->modPhase[0] = 0;
    this->modPhase[1] = 0.25;
    this->modPhase[2] = 0.5;
    this->modPhase[3] = 0.75;

    normalizer.init(4096);

    for(int i = 0; i < DELAY_LINES; i++) {
        multitapDelay[i].init(sampleRate, 1.0);
        multitapDelay[i].setDelayTime(delayTimes[i]*delayTime);
        lowPassFilter[i].init(sampleRate);
        lowPassFilter[i].setResonance(0);
        highPassFilter[i].init(sampleRate);
        highPassFilter[i].setResonance(0);
        for(int j = 0; j < ALL_PASS_FILTERS; j++) {
            allPassFilter[i][j].init(sampleRate);
        }
    }
}

void FDNReverb::setDelay(float delay) {
    delayTime = delay;
    for(int i = 0; i < DELAY_LINES; i++) {
        multitapDelay[i].setDelayTime((delayTimes[i] + mod[i]) * delayTime);
    }
}

void FDNReverb::setLowPassFilterFrequency(float frequency) {
    for(int i = 0; i < DELAY_LINES; i++) {
        lowPassFilter[i].setFrequency(frequency);
    }
}

void FDNReverb::setHighPassFilterFrequency(float frequency) {
    for(int i = 0; i < DELAY_LINES; i++) {
        highPassFilter[i].setFrequency(frequency);
    }
}

void FDNReverb::modulate() {
    for(int i = 0; i < DELAY_LINES; i++) {
        modPhase[i] += sampleTime * modRate;
        if(modPhase[i] > 1) {
            modPhase[i] -= 1;
        }
        mod[i] = sinf(modPhase[i] * M_PI * 2) * modDepth;
        multitapDelay[i].setDelayTime((delayTimes[i] + mod[i]) * delayTime);
    }
}

void FDNReverb::process(float in) {
    modulate();

    input[0] = in * ONE_OVER_ROOT_TWO;
    input[1] = in * ONE_OVER_ROOT_TWO;
    input[2] = in * ONE_OVER_ROOT_TWO;
    input[3] = in * ONE_OVER_ROOT_TWO;
    float normFeedbackGain = feedbackGain * ONE_OVER_ROOT_TWO;

    // read delay outputs
    for(int i = 0; i < DELAY_LINES; i++) {
        output[i] = multitapDelay[i].read(); // - input[i];
    }

    //apply feedback matrix
    float feedback[DELAY_LINES];
    for(int i = 0; i < DELAY_LINES; i++) {
        feedback[i] = 0.0;
        for(int j = 0; j < DELAY_LINES; j++) {
            feedback[i] += output[j] * feedbackMatrix[i][j] * feedbackMultiplier;
        }
    }

    // process lines
    for(int i = 0; i < DELAY_LINES; i++) {

        // add feedback
        float value = input[i] + feedback[i] * normFeedbackGain;
        if(lowPass) {
            lowPassFilter[i].process(value);
            value = lowPassFilter[i].low();
        }
        if(highPass) {
            highPassFilter[i].process(value);
            value = highPassFilter[i].high();
        }

        for(int j = 0; j < ALL_PASS_FILTERS; j++) {
            value = allPassFilter[i][j].process(value);        
        }

        multitapDelay[i].write(value);
    }
}

float FDNReverb::getOutput(int channel) {
    return normalizer.process(output[channel] * wetLevel + input[0] * dryLevel);
}