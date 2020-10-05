#ifndef FilterBank_h
#define FilterBank_h

#include "../../modules/BiquadFilter.h"

#define MAX_FILTER_COUNT 40

class FilterBank {
    public:
        FilterBank() {}
        void init(float sampleRate);

        void setSize(int size) { this->size = size; }
        void setFrequencies(float firstFrequency, float frequencyRatio);
        void setResonance(float resonance);

        void setFilterFrequency(int index, float frequency);
        void setFilterGain(int index, float gain);

    private:
        int size;
        BiquadFilter filters[MAX_FILTER_COUNT];

};

#endif
