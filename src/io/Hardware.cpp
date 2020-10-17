#include "Hardware.h"

Hardware Hardware::hw;

void Hardware::init() {
    display.init();
    encoderButton.update();
    analogReadResolution(12);
}
