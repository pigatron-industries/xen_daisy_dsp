#include "Hardware.h"

void Hardware::init() {
    #if defined(XEN_TFT)
        tft.init();
        tft.setRotation(3);
        tft.fillScreen(TFT_BLACK);
        tft.setTextSize(1);
    #endif
    encoderButton.update();
}