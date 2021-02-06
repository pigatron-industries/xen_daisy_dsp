#ifndef PhaseDistortionOscillator_h
#define PhaseDistortionOscillator_h

#include "../wavetable/WaveTableOscillator.h"
#include "../Envelope.h"

class PhaseDistortionOscillator
{
    public:
        void init(float sampleRate, int tableSize = 256);
        float process();

        Envelope& getEnvelope() { return envelope; }
        WaveTableOscillator& getOscillator() { return oscillator; }

        void setFrequency(float frequency);
        void setPhaseOffset(float phaseOffset) { this->phaseOffset = phaseOffset; }

    private:
        WaveTableOscillator oscillator;
        Envelope envelope;

        float sampleRate;
        float phaseOffset;
};

#endif