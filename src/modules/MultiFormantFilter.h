#ifndef MultiFormantFilter_h
#define MultiFormantFilter_h

#include <inttypes.h>
#include "FormantFilter.h"

template <uint8_t SIZE>
class MultiFormantFilter {
    public:
        MultiFormantFilter() {}
        void init(float sampleRate);
        float process(float in);
        void setFormants(Formant formants[SIZE]);

    private:
        FormantFilter filters[SIZE];

};


template <uint8_t SIZE>
void MultiFormantFilter<SIZE>::init(float sampleRate) {
    for(uint8_t i = 0; i < SIZE; i++) {
        filters[i].init(sampleRate);
    }
}

template <uint8_t SIZE>
void MultiFormantFilter<SIZE>::setFormants(Formant formants[SIZE]) {
    for(uint8_t i = 0; i < SIZE; i++) {
        filters[i].setFormant(formants[i]);
    }
}

template <uint8_t SIZE>
float MultiFormantFilter<SIZE>::process(float in) {
    float out = 0;
    for(uint8_t i = 0; i < SIZE; i++) {
        out += filters[i].process(in);
    }
    return out;
}

#endif