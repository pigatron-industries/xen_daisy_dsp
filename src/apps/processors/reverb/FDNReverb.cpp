#include "FDNReverb.h"
#include "math.h"

void FDNReverb::init(float sampleRate) {
    this->sampleRate = sampleRate;
    this->modUpdateTime = float(modUpdateSamples) / sampleRate;
    this->modPhase[0] = 0;
    this->modPhase[1] = 0.25;
    this->modPhase[2] = 0.5;
    this->modPhase[3] = 0.75;

    for(int i = 0; i < DELAY_LINES; i++) {
        multitapDelay[i].init(sampleRate, 1.0);
        multitapDelay[i].setDelayTime(delayTimes[i]*delayTime);
        allPassFilter[i].init(sampleRate, 1.0);
        allPassFilter[i].setDelayTime(0.1);
        lowPassFilter[i].init(sampleRate);
        lowPassFilter[i].setResonance(0);
        highPassFilter[i].init(sampleRate);
        highPassFilter[i].setResonance(0);
    }
}

void FDNReverb::setDelay(float delay) {
    delayTime = delay;
    for(int i = 0; i < DELAY_LINES; i++) {
        multitapDelay[i].setDelayTime((delayTimes[i] + mod[i]) * delayTime);
        allPassFilter->setDelayTime(delay);
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
        modPhase[i] += modUpdateTime * modRate;
        if(modPhase[i] > 1) {
            modPhase[i] -= 1;
        }
        mod[i] = sinf(modPhase[i] * M_PI * 2) * modDepth;
        multitapDelay[0].setDelayTime((delayTimes[i] + mod[i]) * delayTime);
    }
}

void FDNReverb::process(float in) {
    input = in;
    float normIn = in * ONE_OVER_ROOT_TWO;
    float normFeedbackGain = feedbackGain * ONE_OVER_ROOT_TWO;

    modUpdateCounter++;
    if(modUpdateCounter == modUpdateSamples) {
        modulate();
        modUpdateCounter = 0;
    }

    float feedback[DELAY_LINES];

    // read delay outputs
    for(int i = 0; i < DELAY_LINES; i++) {
        output[i] = multitapDelay[i].read();
    }

    //apply feedback matrix
    for(int i = 0; i < DELAY_LINES; i++) {
        feedback[i] = 0.0;
        for(int j = 0; j < DELAY_LINES; j++) {
            feedback[i] += output[j] * feedbackMatrix[i][j] * feedbackMultiplier;
        }
    }
    // faster to hard code matrix if it won't change:
    // feedback[0] = delayOut[1] + delayOut[2];
    // feedback[1] = 0 - delayOut[0] - delayOut[3];
    // feedback[2] = delayOut[0] - delayOut[3];
    // feedback[3] = delayOut[1] - delayOut[2];

    // process lines
    for(int i = 0; i < DELAY_LINES; i++) {
        // add feedback
        float value = normIn + feedback[i] * normFeedbackGain;
        if(lowPass) {
            lowPassFilter[i].process(value);
            value = lowPassFilter[i].low();
        }
        if(highPass) {
            highPassFilter[i].process(value);
            value = highPassFilter[i].high();
        }
        //value = allPassFilter[i].process(value);
        multitapDelay[i].write(value);
    }
}

float FDNReverb::getOutput(int channel) {
    return output[channel] * wetLevel + input * dryLevel;
}