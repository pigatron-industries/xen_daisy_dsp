#ifndef Formant_h
#define Formant_h

#include <inttypes.h>

class Formant {
    public:
        Formant(uint16_t _frequency, uint16_t _bandwidth, float _gain) : 
            frequency(_frequency), bandwidth(_bandwidth), gain(_gain) {}
        uint16_t frequency;
        uint16_t bandwidth;
        float gain;
};

#endif