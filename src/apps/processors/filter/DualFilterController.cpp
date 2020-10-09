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

    if(Hardware::hw.encoder.getDirection() == RotaryEncoder::Direction::CLOCKWISE) {
        if(displayPage.selectedItem != -1) {
            FilterWrapper& filter = displayPage.selectedItem == FIELD_FILTER1_TYPE ? filter1 : filter2;
            FilterWrapper::FilterType newType = static_cast<FilterWrapper::FilterType>((filter.getType() + 1)%(FilterWrapper::FilterType::MOOG_LADDER + 1));
            filter.setType(newType);
            displayPage.setText(displayPage.selectedItem, getFilterTypeText(filter.getType()));
        }
    }
    if(Hardware::hw.encoderButton.pressed()) {
        displayPage.nextSelection();
    }
    
    displayPage.setText(FIELD_FILTER1_FREQ, String(frequencyInput1.getFrequency(), 2));
    displayPage.setText(FIELD_FILTER2_FREQ, String(frequencyInput2.getFrequency(), 2));
}

void DualFilterController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        out[LEFT][i] = filter1.process(in[LEFT][i]);
        out[RIGHT][i] = filter2.process(in[RIGHT][i]);
    }
}


void DualFilterController::render() {
}

//void DualFilterController::renderFrequencies() {
    // #if defined(XEN_TFT)
    //     hw.tft.setTextColor(TFT_DARKCYAN, TFT_BLACK);
    //     hw.tft.setCursor(TEXT_INDENT, LINE_HEIGHT*2+1, 2);
    //     hw.tft.print(frequencyInput1.getFrequency(), 1);
    //     hw.tft.print("    ");

    //     hw.tft.setTextColor(TFT_DARKCYAN, TFT_BLACK);
    //     hw.tft.setCursor(TEXT_INDENT, LINE_HEIGHT*4+1, 2);
    //     hw.tft.print(frequencyInput2.getFrequency(), 1);
    //     hw.tft.print("    ");
    // #endif
//}

char* DualFilterController::getFilterTypeText(FilterWrapper::FilterType type) {
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
