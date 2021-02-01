#ifndef PhaseDistortion_h
#define PhaseDistortion_h

#include "TransferFunction.h"
#include "../oscillators/Oscillator.h"
#include "../Envelope.h"

class PhaseDistortion
{
    public:
        void init(float sampleRate, TransferFunction* transferFunction);
        float process();

        void setFrequency(float frequency);
        void setPhaseOffset(float phaseOffset) { this->phaseOffset = phaseOffset; }

    private:
        pigatron::Oscillator oscillator;
        TransferFunction* transferFunction;
        Envelope envelope;

        float sampleRate;
        float frequency;
        float phase;
        float phaseOffset;
        float phaseIncrement;

        void calcPhaseIncrement();
};

#endif