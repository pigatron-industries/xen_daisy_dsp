#include "TappableDelayLine.h"
#include "../../io/MemPool.h"

void TappableDelayLine::init(size_t bufferSize) { 
    this->bufferSize = bufferSize;
    buffer = new (MemPool::allocate(sizeof(float)*bufferSize)) float[bufferSize];
    reset();
}

void TappableDelayLine::reset() {
    for(size_t i = 0; i < bufferSize; i++) {
        buffer[i] = 0.0;
    }
    writePointer = 0;
    delay = 1;
}

void TappableDelayLine::setDelay(size_t delay) {
    frac  = 0.0f;
    this->delay = delay < bufferSize ? delay : bufferSize - 1;
}

void TappableDelayLine::setDelay(float delay)
{
    int32_t int_delay = static_cast<int32_t>(delay);
    frac = delay - static_cast<float>(int_delay);
    this->delay = static_cast<size_t>(int_delay) < bufferSize ? int_delay : bufferSize - 1;
}