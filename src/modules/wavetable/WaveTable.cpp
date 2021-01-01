#include "WaveTable.h"

#include "../../io/MemPool.h"
#include "../../util/util.h"
#include "../filters/BiquadFilter.h"

void WaveTable::init(float sampleRate, size_t tableSize) {
    this->sampleRate = sampleRate;
    this->sampleRateReciprocal = 1/sampleRate;
    this->tableSize = tableSize;
    this->antialiased = false;
    for(int i = 0; i < TABLE_COUNT; i++) {
        table[i] = new (MemPool::allocate(sizeof(float)*tableSize)) float[tableSize];
        zeroBuffer(table[i], tableSize);
    }
}

void WaveTable::init(float sampleRate, size_t tableSize, WaveTable& waveTable) {
    this->sampleRate = sampleRate;
    this->sampleRateReciprocal = 1/sampleRate;
    this->tableSize = tableSize;
    this->antialiased = waveTable.antialiased;
    for(int i = 0; i < TABLE_COUNT; i++) {
        this->table[i] = waveTable.getTables()[i];
    }
}

void WaveTable::setTableSample(int index, float sample) {
    if(index < tableSize) {
        table[0][index] = sample;
    }
}

void WaveTable::addTableSample(int index, float sample) {
    if(index < tableSize) {
        table[0][index] += sample;
    }
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
    if(!antialiased) {
        return 0;
    }
    float frequencyBucket = 50;
    int index = 0;
    while(frequency > frequencyBucket && index < TABLE_COUNT) {
        index++;
        frequencyBucket *= 2;
    }
    return index;
}

void WaveTable::antialias() {
    float frequency = 50;
    
    antialiased = true;
    for(int i = 1; i < TABLE_COUNT; i++) {
        frequency *= 2;
        calcAntialiased(getTableForFrequency(frequency), frequency);
    }
}

void WaveTable::calcAntialiased(int tableIndex, float frequency) {
    float oversampleRate = frequency * tableSize;

    Serial.println(frequency);
    Serial.println(tableIndex);
    Serial.println(oversampleRate);

    BiquadFilter filter;
    filter.setType(BiquadFilter::FilterType::LOWPASS);
    filter.init(oversampleRate);

    for(int j = 0; j < 2; j++) {
        for(int i = 0; i < tableSize; i++) {
            filter.setFrequency(15000);
            table[tableIndex][i] = filter.process(table[0][i]);
            //table[tableIndex][i] = table[0][i];
        }
    }
}