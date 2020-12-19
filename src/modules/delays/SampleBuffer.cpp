#include "SampleBuffer.h"
#include "../../io/MemPool.h"

void SampleBuffer::init(size_t bufferSize) { 
    this->bufferSize = bufferSize;
    this->sampleSize = bufferSize;
    buffer = new (MemPool::allocate(sizeof(float)*bufferSize)) float[bufferSize];
    reset();
    clear();
}

void SampleBuffer::reset() {
    writePointer = 0;
    readPointer = 0;
    sampleFull = false;
    bufferFull = false;
}

void SampleBuffer::clear() {
    for(size_t i = 0; i < bufferSize; i++) {
        buffer[i] = 0.0;
    }
}

void SampleBuffer::setSampleSize(size_t sampleSize) {
    if(sampleSize <= bufferSize) {
        this->sampleSize = sampleSize;
    } else {
        this->sampleSize = bufferSize;
    }
}