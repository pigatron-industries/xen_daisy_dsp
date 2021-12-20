#include "Hardware.h"
#include <DaisyDuino.h>

Hardware Hardware::hw;

DSY_SDRAM_BSS float Hardware::permMemBuffer[SDRAM_PERM_SIZE];
DSY_SDRAM_BSS float Hardware::tempMemBuffer[SDRAM_TEMP_SIZE];

void Hardware::init() {
    display.init();
    encoderButton.update();
    analogReadResolution(12);
}
