#include "Vocalizer.h"
#include <math.h>

Formant vocalFormants[5][5][5] = { 
    { BASS_I, BASS_E, BASS_A, BASS_O, BASS_U },
    { TENOR_I, TENOR_E, TENOR_A, TENOR_O, TENOR_U },
    { COUNTERTENOR_I, COUNTERTENOR_E, COUNTERTENOR_A, COUNTERTENOR_O, COUNTERTENOR_U },
    { ALTO_I, ALTO_E, ALTO_A, ALTO_O, ALTO_U },
    { SOPRANO_I, SOPRANO_E, SOPRANO_A, SOPRANO_O, SOPRANO_U }
};

void Vocalizer::init(float sampleRate) {
    filter.init(sampleRate);
}

float Vocalizer::process(float in) {
    return filter.process(in);
}

void Vocalizer::setVowel(float _vowel) {
    vowel = _vowel;
    calculateFormants();
}

void Vocalizer::setRange(float _range) {
    range = _range;
    calculateFormants();
}

void Vocalizer::setPitch(float _pitch) {
    pitch = _pitch;
    calculateFormants();
}

void Vocalizer::setVowelAndRange(float _vowel, float _range) {
    vowel = _vowel;
    range = _range;
    calculateFormants();
}

void Vocalizer::calculateFormants() {
    calculateFractions();
    Formant* formants1a = vocalFormants[rangeInt][vowelInt];
    Formant* formants2a = vocalFormants[rangeInt+1][vowelInt];
    Formant* formants1b = vocalFormants[rangeInt][vowelInt+1];
    Formant* formants2b = vocalFormants[rangeInt+1][vowelInt+1];

    Formant interpolatedFormants[VOCAL_FORMANT_SIZE];
    for(uint8_t i = 0; i < VOCAL_FORMANT_SIZE; i++) {
        interpolatedFormants[i] = Formant::interpolate(formants1a[i], formants2a[i], formants1b[i], formants2b[i], rangeFraction, vowelFraction);
        interpolatedFormants[i].frequency = interpolatedFormants[i].frequency * pitch;
    }

    filter.setFormants(interpolatedFormants);
}

void Vocalizer::calculateFractions() {
    float vowelMin;
    vowelFraction = modf(vowel, &vowelMin);
    vowelInt = vowelMin;
    if(vowelInt >= 4) {
        vowelInt = 3;
        vowelFraction = 1;
    }

    float rangeMin;
    rangeFraction = modf(range, &rangeMin);
    rangeInt = rangeMin;
    if(rangeInt >= 4) {
        rangeInt = 3;
        rangeFraction = 1;
    }
}