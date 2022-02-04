#ifndef Vowelizer_h
#define Vowelizer_h

#include "modules/filters/MultiFormantFilter.h"
#include "formants.h"

class Vowelizer {
    public:
        Vowelizer() {}
        virtual void init(float sampleRate);
        float process(float in);

        // 0=i 1=e 2=a 3=o 5=u
        void setVowel(float vowel);
        // 0=bass 1=tenor 2=countertenor 3=alto 4=soprano
        void setRange(float range);
        void setPitch(float pitch);
        void setVowelAndRange(float vowel, float range);
        void setResonance(float resonance);

    private:
        MultiFormantFilter<VOCAL_FORMANT_SIZE> filter;

        float vowel;
        float range;
        float pitch;

        uint8_t vowelInt;
        float vowelFraction;
        uint8_t rangeInt;
        float rangeFraction;

        void calculateFractions();
        void calculateFormants();

};

#endif