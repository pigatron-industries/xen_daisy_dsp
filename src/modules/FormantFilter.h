#ifndef FormantFilter_h
#define FormantFilter_h

#include <inttypes.h>
#include "DaisyDuino.h"
#include "data/Formant.h"

class FormantFilter {
    public:
        FormantFilter();
        void init(float sampleRate);
        float process(float in);

        void setFormant(Formant formant);

    private:
        Formant formant;
        Svf highPassFilter;
        Svf lowPassFilter;

};

#endif