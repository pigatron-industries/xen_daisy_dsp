#include "FilterBankController.h"

#define LEFT 0
#define RIGHT 1

void FilterBankController::init(float sampleRate) {
    filterBank.init(sampleRate);
    filterBank.setSize(10);
    filterBank.setBankBandPass(32.0, 243/128);

    displayPage.initTitle("Filter Bank");
}

void FilterBankController::update() {
}

void FilterBankController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        out[LEFT][i] = filterBank.process(in[LEFT][i]);
    }
}
