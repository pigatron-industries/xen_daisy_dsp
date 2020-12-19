#ifndef SampleBuffer_h
#define SampleBuffer_h
#include <stdlib.h>
#include <stdint.h>

class SampleBuffer
{
    public:
        SampleBuffer() {}

        void init(size_t bufferSize);
        void reset();
        void clear();

        void setSampleSize(size_t sampleSize);

        bool write(const float sample);
        inline const float read();
        inline const bool readIncrement();

        bool isSampleFull() { return sampleFull; }
        bool isBufferFull() { return bufferFull; }

    private:
        size_t bufferSize;
        size_t sampleSize;
        float* buffer;
        
        bool sampleFull;
        bool bufferFull;

        size_t writePointer;
        size_t readPointer;
};


inline bool SampleBuffer::write(const float sample) {
    buffer[writePointer] = sample;
    writePointer++;
    if(!sampleFull && writePointer >= sampleSize) {
        sampleFull = true;
    }
    if(writePointer >= bufferSize) {
        bufferFull = true;
        writePointer = 0;
    }
    return sampleFull;
}

inline const float SampleBuffer::read() {
    return buffer[readPointer];
}

inline const bool SampleBuffer::readIncrement() {
    readPointer++;
    if(readPointer > sampleSize) {
        readPointer = 0;
        return true;
    } else {
        return false;
    }
}

#endif
