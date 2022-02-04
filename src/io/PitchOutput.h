#ifndef PitchOutput_h
#define PitchOutput_h

#include <inttypes.h>

class [[deprecated]] PitchOutput {
    public:
        PitchOutput(uint8_t _pin) : pin(_pin) {
        }

        inline void update() {
            voltage = logf(frequency/zeroFrequency) / logf(2);
            value = ((voltage-5)/-10)*255;
            analogWrite(pin, value);
        }

        inline void setFrequency(float frequency) {
            this->frequency = frequency;
            update();
        }

        inline void setZeroFrequency(float _zeroFrequency) {
            zeroFrequency = _zeroFrequency;
        }

    private:
        uint8_t pin;

        uint32_t value;
        float voltage;
        float frequency;

        float zeroFrequency = 440;

};

#endif