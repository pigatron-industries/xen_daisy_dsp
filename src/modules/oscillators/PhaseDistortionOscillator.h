#ifndef PhaseDistortionOscillator_h
#define PhaseDistortionOscillator_h

#include "../oscillators/Oscillator.h"
#include "../Envelope.h"

class PhaseDistortionOscillator
{
    public:
        void init(float sampleRate);
        float process();

        void setFrequency(float frequency);
        void setPhaseOffset(float phaseOffset) { this->phaseOffset = phaseOffset; }
        Envelope& getEnvelope() { return envelope; }

    private:
        pigatron::Oscillator oscillator;
        Envelope envelope;

        float sampleRate;
        float phaseOffset;
};

#endif