#ifndef WaveTable_h
#define WaveTable_h

#include <stdlib.h>

class WaveTable {
    public:
        WaveTable() {}
        void init(float sampleRate, size_t tableSize);
        void init(float sampleRate, size_t tableSize, float* table);
        float process();

        void setFrequency(float frequency);
        void setFrequencyTable(float frequency);

        size_t getSize() { return tableSize; }
        float* getTable() { return table; }
        void setTableSample(int index, float sample);
        void addTableSample(int index, float sample);
        float read(float position);

    private:
        float* table;
        size_t tableSize;

        float sampleRate;
        float sampleRateReciprocal;
        float position;
        float increment;
        float frequency;
};

#endif
