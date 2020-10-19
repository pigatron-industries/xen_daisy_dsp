#ifndef Formant_h
#define Formant_h

#include <inttypes.h>

class Formant {
    public:
        Formant() {}
        Formant(uint16_t _frequency, uint16_t _bandwidth, float _gain) : 
            frequency(_frequency), bandwidth(_bandwidth), gain(_gain) {}
        uint16_t frequency;
        uint16_t bandwidth;
        float gain;

        static Formant interpolate(Formant formant1, Formant formant2, float x);
        static Formant interpolate(Formant formant1a, Formant formant2a, Formant formant1b, Formant formant2b, float x, float y);
};

#endif