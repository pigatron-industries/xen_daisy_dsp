#include "Formant.h"


Formant Formant::interpolate(Formant formant1, Formant formant2, float x) {
    return Formant((formant1.frequency + formant2.frequency)/2, 
                   (formant1.bandwidth + formant2.bandwidth)/2,
                   (formant1.gain + formant2.gain)/2);
}

Formant Formant::interpolate(Formant formant1a, Formant formant2a, Formant formant1b, Formant formant2b, float x, float y) {
    Formant formanta = interpolate(formant1a, formant2a, x);
    Formant formantb = interpolate(formant1b, formant2b, x);
    return interpolate(formanta, formantb, y);
}