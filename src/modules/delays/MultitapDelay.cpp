#include "MultitapDelay.h"
#include <math.h>
#include "../../util/util.h"

void MultitapDelay::init(float sampleRate, float maxDelay) {
    this->sampleRate = sampleRate;
    this->tapCount = 1;
    delayLine.init(sampleRate*maxDelay);
    setTap(0, maxDelay, 1);
}

void MultitapDelay::setTap(int tapIndex, float delayTime, float tapGain) {
    tapPositions[tapIndex] = delayTime*sampleRate;
    tapGains[tapIndex] = tapGain;
}

void MultitapDelay::setTap(int tapIndex, float delayTime) {
    tapPositions[tapIndex] = delayTime*sampleRate;
}

void MultitapDelay::setDelayTime(float delayTime) {
    tapPositions[0] = delayTime*sampleRate;
}

float MultitapDelay::process(float in) {
    float output = 0.0;
    for(int i = 0; i < tapCount; i++) {
        output += delayLine.read(tapPositions[i]) * tapGains[i];
    }

    delayLine.write(in);
    return output + in * dryGain;
}

void MultitapDelay::createTaps(int tapCount, float tapLength, float tapDecay, float tapGain) {
    this->tapCount = tapCount;

    // used to adjust the volume of the overall output as it grows when we add more taps
    float tapCountFactor = 1.0 / (1 + sqrt(tapCount / MAX_TAPS));
    float sumTapLengths = 0.0;
    for (size_t i = 0; i < tapCount; i++) {
        sumTapLengths += randf(0.1, 1.0); //randf(0.1, 1.0);
        tapPositions[i] = sumTapLengths;
    }

    // rescale random tap positions so they fit passed in tap length
    float tapLengthSamples = tapLength*sampleRate;
    float scaleLength = tapLengthSamples / sumTapLengths;
    sumTapLengths = sumTapLengths * scaleLength;
    for (size_t i = 0; i < tapCount; i++) {
        tapPositions[i] = tapPositions[i] * scaleLength;
        Serial.println("tap positions");
        Serial.println(tapPositions[i]);
    }

    float sumGains = 0.0;
    for (size_t i = 0; i < tapCount; i++) {
        // when decay set to 0, there is no decay, when set to 1, the gain at the last sample is 0.01 = -40dB
        float g = powf(10, -tapDecay * 2 * tapPositions[i] / (sumTapLengths + 1));
        //float tap = randf(-1.0, 1.0) * tapCountFactor;
        tapGains[i] = g * tapGain * tapCountFactor; // * tap;
        Serial.println("tap gains");
        Serial.println(tapGains[i]);
    }

    dryGain = (1 - tapGain);
}