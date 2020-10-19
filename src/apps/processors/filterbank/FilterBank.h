#ifndef FilterBank_h
#define FilterBank_h

#include "../../../modules/filters/FilterWrapper.h"

#define MAX_FILTER_COUNT 40

class FilterBank {
    public:
        FilterBank() {}
        void init(float sampleRate);
        float process(float in);
        float processSerial(float in);
        float processParallel(float in);

        int getSize() { return size; }
        FilterWrapper& getFilter(int index) { return filters[index]; }
        float getAllOutput() { return all; }
        float getEvenOutput() { return even; }
        float getOddOutput() { return odd; }

        void setSize(int size) { this->size = size; }
        void setFilterResonance(int index, float resonance);
        void setFilterFrequency(int index, float frequency);
        void setFilterGain(int index, float gain);

        void setBankBandPass(float firstFrequency, float frequencyRatio);
        void setBankLowBandHighPass(float lowPassFrequency, float highPassFrequency, float firstBandFrequency, float frequencyRatio);

        enum ProcessOrder {
            PARALLEL, SERIES
        };

    private:
        int size;
        ProcessOrder processOrder;
        FilterWrapper filters[MAX_FILTER_COUNT];

        float all, even, odd;
};

#endif
