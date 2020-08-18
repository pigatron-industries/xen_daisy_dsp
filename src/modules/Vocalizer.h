#ifndef Vocalizer_h
#define Vocalizer_h

#include "data/formants.h"
#include "MultiFormantFilter.h"

class Vocalizer {
    public:
        Vocalizer() {}

    private:
        MultiFormantFilter<VOCAL_FORMANT_SIZE> filter;

};

#endif