#include "FilterController.h"

#define LEFT 0
#define RIGHT 1

void FilterController::init(float sampleRate) {
    filter.init(sampleRate);
}

void FilterController::update() {
    frequencyInput.update();
    resonanceInput.update();

    if(encoder.getDirection() == RotaryEncoder::Direction::CLOCKWISE) {
        FilterWrapper::FilterType newType = static_cast<FilterWrapper::FilterType>((filter.getType() + 1)%(FilterWrapper::FilterType::MOOG_LADDER + 1));
        filter.setType(newType);
    }

    filter.setFrequency(frequencyInput.getFrequency());
    filter.setResonance(resonanceInput.getValue());
}

void FilterController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        out[LEFT][i] = filter.process(in[LEFT][i]);
    }
}