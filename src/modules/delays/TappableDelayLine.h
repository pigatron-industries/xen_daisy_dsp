#ifndef TappableDelayLine_h
#define TappableDelayLine_h
#include <stdlib.h>
#include <stdint.h>

class TappableDelayLine
{
    public:
        TappableDelayLine() {}

        void init(size_t bufferSize);
        void reset();

        void setDelay(size_t delay);
        void setDelay(float delay);
        void write(const float sample);
        inline const float read() const;
        inline const float read(size_t delay) const;
        inline const float read(float delay) const;

    private:
        float  frac;
        size_t delay;
        size_t writePointer;
        size_t bufferSize;
        float* buffer;
};


inline void TappableDelayLine::write(const float sample)
{
    buffer[writePointer] = sample;
    writePointer = (writePointer - 1 + bufferSize) % bufferSize;
}

inline const float TappableDelayLine::read() const {
    float a = buffer[(writePointer + delay) % bufferSize];
    float b = buffer[(writePointer + delay + 1) % bufferSize];
    return a + (b - a) * frac;
}

inline const float TappableDelayLine::read(size_t delay) const {
    return buffer[(writePointer + delay) % bufferSize];
}

inline const float TappableDelayLine::read(float delay) const {
    int32_t intDelay = static_cast<int32_t>(delay);
    float frac = delay - static_cast<float>(intDelay);
    intDelay = static_cast<size_t>(intDelay) < bufferSize ? intDelay : bufferSize - 1;
    float a = buffer[(writePointer + intDelay) % bufferSize];
    float b = buffer[(writePointer + intDelay + 1) % bufferSize];
    return a + (b - a) * frac;
}

#endif
