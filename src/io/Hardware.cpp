#include "Hardware.h"

void Hardware::init() {
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(1);
    encoderButton.update();
}