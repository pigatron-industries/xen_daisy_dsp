#ifndef FormantFilter_h
#define FormantFilter_h

#include <DaisyDSP.h>
#include <inttypes.h>
#include "Formant.h"

class FormantFilter {
    public:
        FormantFilter();
        void init(float sampleRate);
        float process(float in);

        void setFormant(Formant formant);
        void setResonance(float resonance);

    private:
        Formant formant;
        Svf highPassFilter;
        Svf lowPassFilter;

};

#endif