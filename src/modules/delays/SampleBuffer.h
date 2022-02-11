#ifndef deprecated_SampleBuffer_h
#define deprecated_SampleBuffer_h
#include <stdlib.h>
#include <stdint.h>

namespace deprecated {

    class SampleBuffer
    {
        public:
            SampleBuffer() {}

            void init(size_t bufferSize);
            void reset();
            void clear();

            void setSampleSize(size_t sampleSize);

            bool write(const float sample);
            const float read();
            const float read(float increment);

            bool isSampleFull() { return sampleFull; }
            bool isBufferFull() { return bufferFull; }
            bool isReadFull() { return readFull; }

        private:
            size_t bufferSize;
            size_t sampleSize;
            float* buffer;
            
            bool sampleFull;
            bool bufferFull;
            bool readFull;

            size_t writePointer;
            size_t readPointer;
            float readFraction;

            void readIncrement();
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
        float sample = buffer[readPointer];
        readIncrement();
        return sample;
    }

    inline const float SampleBuffer::read(float increment) {
        float sample = buffer[readPointer];
        readIncrement();
        return sample;
    }

    inline void SampleBuffer::readIncrement() {
        readPointer++;
        if(readPointer > sampleSize) {
            readPointer = 0;
            readFull = true;
        } else {
            readFull = false;
        }
    }
    
}

#endif
