#include "PhaseDistortion.h"

void PhaseDistortion::init(float sampleRate, TransferFunction* transferFunction) { 
    this->transferFunction = transferFunction;
    this->sampleRate = sampleRate;
    frequency = 100;
    phaseOffset = 0;
    oscillator.init(sampleRate);
    oscillator.setWaveform(pigatron::Oscillator::WAVE_SIN);
    calcPhaseIncrement();
}

void PhaseDistortion::setFrequency(float frequency) { 
    this->frequency = frequency; 
    oscillator.setFrequency(frequency);
    calcPhaseIncrement(); 
}

float PhaseDistortion::process() {
    float out = oscillator.process();
    phase += phaseIncrement;
    if(phase > 1) {
        phase -= 1;
    }

    float distortedPhase = transferFunction->process(phase) + phaseOffset;
    if(distortedPhase > 1) {
        distortedPhase -= 1;
    }

    oscillator.setPhase(distortedPhase);
    return out;
}

void PhaseDistortion::calcPhaseIncrement() {
    phaseIncrement = frequency / sampleRate;
}