#include "DualFilterController.h"

#define LEFT 0
#define RIGHT 1

void DualFilterController::init(float sampleRate) {
    filter1.init(sampleRate);
    filter2.init(sampleRate);
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

    if(hw.encoder.getDirection() == RotaryEncoder::Direction::CLOCKWISE) {
        if(selectedChannel > 0) {
            FilterWrapper& filter = selectedChannel == 1 ? filter1 : filter2;
            FilterWrapper::FilterType newType = static_cast<FilterWrapper::FilterType>((filter.getType() + 1)%(FilterWrapper::FilterType::MOOG_LADDER + 1));
            filter.setType(newType);
            render();
        }
    }
    if(hw.encoderButton.pressed()) {
        channelSelect();
        render();
    }

    renderFrequencies();
}

void DualFilterController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        out[LEFT][i] = filter1.process(in[LEFT][i]);
        out[RIGHT][i] = filter2.process(in[RIGHT][i]);
    }
}

void DualFilterController::channelSelect() {
    selectedChannel = selectedChannel<2 ? selectedChannel+1 : 0;
}

void DualFilterController::render() {
    hw.tft.setCursor(TEXT_INDENT, LINE_HEIGHT+1, 2);
    hw.tft.fillRect(0, LINE_HEIGHT+1, hw.tft.width()-1, LINE_HEIGHT, selectedChannel == 1 ? TFT_NAVY : TFT_BLACK);
    hw.tft.setTextColor(selectedChannel == 1 ? TFT_CYAN : TFT_DARKCYAN, selectedChannel == 1 ? TFT_NAVY : TFT_BLACK);
    hw.tft.print("1 > ");
    printFilterType(filter1.getType());

    hw.tft.setCursor(2, LINE_HEIGHT*3+1, 2);
    hw.tft.fillRect(0, LINE_HEIGHT*3+1, hw.tft.width()-1, LINE_HEIGHT, selectedChannel == 2 ? TFT_NAVY : TFT_BLACK);
    hw.tft.setTextColor(selectedChannel == 2 ? TFT_CYAN : TFT_DARKCYAN, selectedChannel == 2 ? TFT_NAVY : TFT_BLACK);
    hw.tft.print("2 > ");
    printFilterType(filter2.getType());

    renderFrequencies();
}

void DualFilterController::renderFrequencies() {
    hw.tft.setTextColor(TFT_DARKCYAN, TFT_BLACK);
    hw.tft.setCursor(TEXT_INDENT, LINE_HEIGHT*2+1, 2);
    hw.tft.print(frequencyInput1.getFrequency(), 1);
    hw.tft.print("    ");

    hw.tft.setTextColor(TFT_DARKCYAN, TFT_BLACK);
    hw.tft.setCursor(TEXT_INDENT, LINE_HEIGHT*4+1, 2);
    hw.tft.print(frequencyInput2.getFrequency(), 1);
    hw.tft.print("    ");
}

void DualFilterController::printFilterType(FilterWrapper::FilterType type) {
    switch(type) {
        case FilterWrapper::FilterType::SVF_BAND_PASS:
            hw.tft.print("SVF Band Pass   ");
            break;
        case FilterWrapper::FilterType::SVF_LOW_PASS:
            hw.tft.print("SVF Low Pass    ");
            break;
        case FilterWrapper::FilterType::SVF_HIGH_PASS:
            hw.tft.print("SVF High Pass   ");
            break;
        case FilterWrapper::FilterType::SVF_NOTCH:
            hw.tft.print("SVF Notch       ");
            break;
        case FilterWrapper::FilterType::SVF_PEAK:
            hw.tft.print("SVF Peak        ");
            break;
        case FilterWrapper::FilterType::BIQUAD_BAND_PASS:
            hw.tft.print("Biquad Band Pass");
            break;
        case FilterWrapper::FilterType::MOOG_LADDER:
            hw.tft.print("Moog Ladder     ");
            break;
    }
}
