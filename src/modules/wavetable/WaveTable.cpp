#include "WaveTable.h"

#include "../../io/MemPool.h"
#include "../../util/util.h"

void WaveTable::init(float sampleRate, size_t tableSize) {
    this->sampleRate = sampleRate;
    this->sampleRateReciprocal = 1/sampleRate;
    this->tableSize = tableSize;
    table = new (MemPool::allocate(sizeof(float)*tableSize)) float[tableSize];
    zeroBuffer(table, tableSize);
}

void WaveTable::init(float sampleRate, size_t tableSize, float* table) {
    this->sampleRate = sampleRate;
    this->sampleRateReciprocal = 1/sampleRate;
    this->tableSize = tableSize;
    this->table = table;
}

void WaveTable::setTableSample(int index, float sample) {
    if(index < tableSize) {
        table[index] = sample;
    }
}

void WaveTable::addTableSample(int index, float sample) {
    if(index < tableSize) {
        table[index] += sample;
    }
}

void WaveTable::setFrequency(float frequency) { 
    increment = (tableSize * frequency) * sampleRateReciprocal;
    setFrequencyTable(frequency);
}

void WaveTable::setFrequencyTable(float frequency) {
    this->frequency = frequency;
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
    float a = table[intPosition % tableSize];
    float b = table[(intPosition + 1) % tableSize];
    return a + (b - a) * fracPosition;
}