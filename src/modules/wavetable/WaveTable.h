#ifndef WaveTable_h
#define WaveTable_h

#include <stdlib.h>

#define TABLE_COUNT 10

class WaveTable {
    public:
        WaveTable() {}
        void init(float sampleRate, size_t tableSize);
        void init(float sampleRate, size_t tableSize, WaveTable& waveTable);
        float process();

        void setFrequency(float frequency);
        void setFrequencyTable(float frequency);

        size_t getSize() { return tableSize; }
        float** getTables() { return table; }
        void setTableSample(int index, float sample);
        void addTableSample(int index, float sample);
        float read(float position);

        void antialias();

    private:
        float* table[TABLE_COUNT];
        size_t tableSize;
        int tableIndex;
        bool antialiased;

        float sampleRate;
        float sampleRateReciprocal;
        float position;
        float increment;
        float frequency;

        int getTableForFrequency(float frequency);
        void calcAntialiased(int tableIndex, float sampleRate);
};

#endif
