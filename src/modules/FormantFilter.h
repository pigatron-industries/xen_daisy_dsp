#ifndef FormantFilter_h
#define FormantFilter_h

#include <inttypes.h>
#include "DaisyDuino.h"
#include "Formant.h"

class FormantFilter {
    public:
        FormantFilter();
        void init(float sampleRate);

        void setFormant(Formant _formant);

    private:

        Svf highPassFilter;
        Svf lowPassFilter;

};

#endif