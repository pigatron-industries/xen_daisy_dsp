#include "FilterBankController.h"

#define LEFT 0
#define RIGHT 1

void FilterBankController::init(float sampleRate) {
    filterBank.init(sampleRate);
    filterBank.setSize(8);
    filterBank.setBankBandPass(32.0, 243.0/128.0);

    displayPage.initTitle("Filter Bank");
}

void FilterBankController::update() {
    gainInput1.update();
    gainInput2.update();
    gainInput3.update();
    gainInput4.update();
    gainInput5.update();
    gainInput6.update();
    gainInput7.update();
    gainInput8.update();
    gainInput9.update();
    gainInput10.update();

    filterBank.setFilterGain(0, gainInput1.getValue());
    filterBank.setFilterGain(1, gainInput2.getValue());
    filterBank.setFilterGain(2, gainInput3.getValue());
    filterBank.setFilterGain(3, gainInput4.getValue());
    filterBank.setFilterGain(4, gainInput5.getValue());
    filterBank.setFilterGain(5, gainInput6.getValue());
    filterBank.setFilterGain(6, gainInput7.getValue());
    // filterBank.setFilterGain(7, gainInput8.getValue());
    // filterBank.setFilterGain(8, gainInput9.getValue());
    filterBank.setFilterGain(7, gainInput10.getValue());

    filterBank.setFilterResonance(0, gainInput1.getValue());
    filterBank.setFilterResonance(1, gainInput2.getValue());
    filterBank.setFilterResonance(2, gainInput3.getValue());
    filterBank.setFilterResonance(3, gainInput4.getValue());
    filterBank.setFilterResonance(4, gainInput5.getValue());
    filterBank.setFilterResonance(5, gainInput6.getValue());
    filterBank.setFilterResonance(6, gainInput7.getValue());
    // filterBank.setFilterResonance(7, gainInput8.getValue());
    // filterBank.setFilterResonance(8, gainInput9.getValue());
    filterBank.setFilterResonance(7, gainInput10.getValue());
}

void FilterBankController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        filterBank.process(in[LEFT][i]);
        out[LEFT][i] = filterBank.getEvenOutput();
        out[RIGHT][i] = filterBank.getOddOutput();
    }
}
