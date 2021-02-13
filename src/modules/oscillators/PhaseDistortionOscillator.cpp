#include "PhaseDistortionOscillator.h"

void PhaseDistortionOscillator::init(float sampleRate, int tableSize, int pointCount) { 
    this->sampleRate = sampleRate;
    phaseOffset = 0;
    oscillator.init(sampleRate, tableSize);

    int envelopePoints = pointCount + 2;
    envelope.init(sampleRate, envelopePoints, 1, true);
    for(int i = 0; i < envelopePoints; i++) {
        envelope.setPoint(i, Point(float(i)/float(envelopePoints), 0));
    }
    envelope.setFrequency(100);
}

void PhaseDistortionOscillator::setFrequency(float frequency) { 
    oscillator.setFrequency(frequency);
    envelope.setFrequency(frequency);
}

float PhaseDistortionOscillator::process() {
    float out = oscillator.process();
    float distortedPhase = envelope.process() + phaseOffset;

    if(distortedPhase > 1) {
        distortedPhase -= 1;
    }

    oscillator.setPhase(distortedPhase);
    return out;
}
