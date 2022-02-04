#ifndef PhaseDistortionOscillator_h
#define PhaseDistortionOscillator_h

#include "../wavetable/WaveTableOscillator.h"
#include "../Envelope.h"

class [[deprecated]] PhaseDistortionOscillator
{
    public:
        void init(float sampleRate, int tableSize = 256, int pointCount = 1);
        float process();

        deprecated::Envelope& getEnvelope() { return envelope; }
        WaveTableOscillator& getOscillator() { return oscillator; }

        void setFrequency(float frequency);
        void setPhaseOffset(float phaseOffset) { this->phaseOffset = phaseOffset; }

    private:
        WaveTableOscillator oscillator;
        deprecated::Envelope envelope;

        float sampleRate;
        float phaseOffset;
};

#endif