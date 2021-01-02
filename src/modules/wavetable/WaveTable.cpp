#include "WaveTable.h"

#include "../../io/MemPool.h"
#include "../../util/util.h"
#include "../filters/BiquadFilter.h"

void WaveTable::init(float sampleRate, size_t tableSize, size_t tableCount) {
    this->sampleRate = sampleRate;
    this->sampleRateReciprocal = 1/sampleRate;
    this->tableSize = tableSize;
    this->tableCount = tableCount <= MAX_TABLES ? tableCount : MAX_TABLES;
    for(int i = 0; i < tableCount; i++) {
        table[i] = new (MemPool::allocate(sizeof(float)*tableSize)) float[tableSize];
        zeroBuffer(table[i], tableSize);
    }
    calcTableFrequencies();
}

void WaveTable::init(float sampleRate, WaveTable& waveTable) {
    this->sampleRate = sampleRate;
    this->sampleRateReciprocal = 1/sampleRate;
    this->tableSize = waveTable.tableSize;
    this->tableCount = waveTable.tableCount;
    for(int i = 0; i < tableCount; i++) {
        this->table[i] = waveTable.getTables()[i];
    }
    calcTableFrequencies();
}

void WaveTable::setTableSample(int index, float sample) {
    if(index < tableSize) {
        for(int i = 0; i < tableCount; i++) {
            table[i][index] = sample;
        }
    }
}

void WaveTable::addTableSample(int index, float sample) {
    if(index < tableSize) {
        for(int i = 0; i < tableCount; i++) {
            table[i][index] += sample;
        }
    }
}

void WaveTable::setTableSample(int tableIndex, int sampleIndex, float sample) {
    table[tableIndex][sampleIndex] = sample;
}

void WaveTable::addTableSample(int tableIndex, int sampleIndex, float sample) {
    table[tableIndex][sampleIndex] += sample;
}

void WaveTable::setFrequency(float frequency) { 
    increment = (tableSize * frequency) * sampleRateReciprocal;
    setFrequencyTable(frequency);
}

void WaveTable::setFrequencyTable(float frequency) {
    this->frequency = frequency;
    tableIndex = getTableForFrequency(frequency);
}

float WaveTable::process() {
    position += increment;
    if(position > tableSize-1) {
        position -= tableSize-1;
    }
    return read(position);
}

float WaveTable::read(float position) {
    int32_t intPosition = static_cast<int32_t>(position);
    float fracPosition = position - static_cast<float>(intPosition);
    intPosition = static_cast<size_t>(intPosition) < tableSize ? intPosition : tableSize - 1;
    float a = table[tableIndex][intPosition % tableSize];
    float b = table[tableIndex][(intPosition + 1) % tableSize];
    return a + (b - a) * fracPosition;
}

int WaveTable::getTableForFrequency(float frequency) {
    int newtableIndex = 0;
    for(int i = 0; i < tableCount; i++) {
        if(frequency < tableFrequency[i]) {
            return i;
        }
    }
    return tableCount-1;
}

void WaveTable::calcTableFrequencies() {
    float baseFrequency = 50;
    float octaveInc = 10.0 / float(tableCount);
    float octave = 0;

    for(int i = 0; i < tableCount; i++) {
        tableFrequency[i] = baseFrequency * powf(2, octave);
        octave += octaveInc;
    }
}