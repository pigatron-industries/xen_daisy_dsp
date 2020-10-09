#include "DualFilterController.h"

#define LEFT 0
#define RIGHT 1

#define FIELD_FILTER1_TYPE 1
#define FIELD_FILTER1_FREQ 2
#define FIELD_FILTER2_TYPE 3
#define FIELD_FILTER2_FREQ 4

void DualFilterController::init(float sampleRate) {
    filter1.init(sampleRate);
    filter2.init(sampleRate);

    displayPage.initTitle("Dual Filter");
    displayPage.initField(FIELD_FILTER1_TYPE, getFilterTypeText(filter1.getType()), true);
    displayPage.initField(FIELD_FILTER1_FREQ, "0", false);
    displayPage.initField(FIELD_FILTER2_TYPE, getFilterTypeText(filter1.getType()), true);
    displayPage.initField(FIELD_FILTER2_FREQ, "0", false);
}

void DualFilterController::update() {
    frequencyInput1.update();
    resonanceInput1.update();
    frequencyInput2.update();
    resonanceInput2.update();
    filter1.setFrequency(frequencyInput1.getFrequency());
    filter1.setResonance(resonanceInput1.getValue());
    filter2.setFrequency(frequencyInput2.getFrequency());
    filter2.setResonance(resonanceInput2.getValue());
}

void DualFilterController::updateDisplay() {
    displayPage.setText(FIELD_FILTER1_FREQ, String(frequencyInput1.getFrequency(), 2));
    displayPage.setText(FIELD_FILTER2_FREQ, String(frequencyInput2.getFrequency(), 2));
}

void DualFilterController::event(UIEvent event, int itemIndex) {
    if(itemIndex > 0) {
        if(event == UIEvent::EVENT_CLOCKWISE) {
            FilterWrapper& filter = displayPage.selectedItem == FIELD_FILTER1_TYPE ? filter1 : filter2;
            FilterWrapper::FilterType newType = static_cast<FilterWrapper::FilterType>((filter.getType() + 1)%(FilterWrapper::FilterType::MOOG_LADDER + 1));
            filter.setType(newType);
            displayPage.setText(itemIndex, getFilterTypeText(filter.getType()));
        } else if (event == UIEvent::EVENT_COUNTERCLOCKWISE) {
            FilterWrapper& filter = displayPage.selectedItem == FIELD_FILTER1_TYPE ? filter1 : filter2;
            FilterWrapper::FilterType newType = static_cast<FilterWrapper::FilterType>(filter.getType() > 0 ? filter.getType() - 1 : FilterWrapper::FilterType::MOOG_LADDER);
            filter.setType(newType);
            displayPage.setText(itemIndex, getFilterTypeText(filter.getType()));
        }
    }
}

void DualFilterController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        out[LEFT][i] = filter1.process(in[LEFT][i]);
        out[RIGHT][i] = filter2.process(in[RIGHT][i]);
    }
}

String DualFilterController::getFilterTypeText(FilterWrapper::FilterType type) {
    switch(type) {
        case FilterWrapper::FilterType::SVF_BAND_PASS:
            return "SVF Band Pass";
            break;
        case FilterWrapper::FilterType::SVF_LOW_PASS:
            return "SVF Low Pass";
            break;
        case FilterWrapper::FilterType::SVF_HIGH_PASS:
            return "SVF High Pass";
            break;
        case FilterWrapper::FilterType::SVF_NOTCH:
            return "SVF Notch";
            break;
        case FilterWrapper::FilterType::SVF_PEAK:
            return "SVF Peak";
            break;
        case FilterWrapper::FilterType::MOOG_LADDER:
            return "Moog Ladder";
            break;
    }
}
