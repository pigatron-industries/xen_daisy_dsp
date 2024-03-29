#ifndef deprecated_WaveTable_h
#define deprecated_WaveTable_h

#include <stdlib.h>
#include <eurorack.h>

#define MAX_TABLES 20

namespace deprecated {

    class WaveTable {
        public:
            WaveTable() {}
            void init(float sampleRate, size_t tableSize, size_t tableCount, MemPool<float>& memPool);
            void init(float sampleRate, WaveTable& waveTable);
            bool isInited() { return inited; }

            float process();
            float read(float position);

            void setFrequency(float frequency);
            void setFrequencyTable(float frequency);

            size_t getSize() { return tableSize; }
            size_t getTableCount() { return tableCount; }
            float getTableFrequency(int tableIndex) { return tableFrequency[tableIndex]; }
            float** getTables() { return table; }
            float getSampleRate() { return sampleRate; }

            void setTableSample(int index, float sample);
            void addTableSample(int index, float sample);
            void setTableSample(int tableIndex, int sampleIndex, float sample);
            void addTableSample(int tableIndex, int sampleIndex, float sample);

            float* getTempBuffer() { return tempBuffer; }
            void addTempBufferToTable(int tableIndex);

        private:
            bool inited = false;

            float* table[MAX_TABLES];
            float tableFrequency[MAX_TABLES];
            size_t tableSize;
            size_t tableCount;

            int tableIndex;

            float sampleRate;
            float sampleRateReciprocal;
            float position;
            float increment;
            float frequency;

            float* tempBuffer;

            int getTableForFrequency(float frequency);
            void calcTableFrequencies();
    };
}

#endif
