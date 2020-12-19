#include "FDNReverb.h"
#include "math.h"

#define ONE_OVER_ROOT_2 0.7071067

void FDNReverb::init(float sampleRate) {
    this->sampleRate = sampleRate;
    float modUpdateTime = float(modUpdateSamples) / sampleRate;

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
        multitapDelay[i].setDelayTime(delayTimes[i]*delayTime + mod[i]*delayTime);
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
    modPhase += modUpdateTime * modRate;
    if(modPhase > 1) {
        modPhase -= 1;
    }

    for(int i = 0; i < DELAY_LINES; i++) {
        mod[i] = sinf(modPhase * M_PI * 2) * modDepth;
        multitapDelay[0].setDelayTime(delayTimes[i]*delayTime + mod[i]*delayTime);
    }
}

float FDNReverb::process(float in) {
    float normIn = in * ONE_OVER_ROOT_2;
    float normFeedbackGain = feedbackGain * ONE_OVER_ROOT_2;

    modUpdateCounter++;
    if(modUpdateCounter == modUpdateTime) {
        modulate();
        modUpdateCounter = 0;
    }

    float delayOut[DELAY_LINES];
    float feedback[DELAY_LINES];
    float output = 0.0;

    // read delay outputs
    for(int i = 0; i < DELAY_LINES; i++) {
        delayOut[i] = multitapDelay[i].read();
        output += delayOut[i];
    }

    //apply feedback matrix
    for(int i = 0; i < DELAY_LINES; i++) {
        feedback[i] = 0.0;
        for(int j = 0; j < DELAY_LINES; j++) {
            feedback[i] += delayOut[j] * feedbackMatrix[i][j];
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

    return output * dryOut + in * wetOut;
}