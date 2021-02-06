#include "PhaseDistortionOscillator.h"

void PhaseDistortionOscillator::init(float sampleRate) { 
    this->sampleRate = sampleRate;
    phaseOffset = 0;
    oscillator.init(sampleRate);
    oscillator.setWaveform(pigatron::Oscillator::WAVE_SIN);
    envelope.init(sampleRate, 3, 1, true);
    envelope.setPoint(0, Point(0, 0));
    envelope.setPoint(1, Point(0.5, 0.5));
    envelope.setPoint(2, Point(1, 1));
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
