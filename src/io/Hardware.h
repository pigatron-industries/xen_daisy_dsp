#ifndef Hardware_h
#define Hardware_h

#include <TFT_eSPI.h>
#include <RotaryEncoder.h>
#include "PushButton.h"

class Hardware {

public:
    Hardware() {}
    void init();

    TFT_eSPI tft = TFT_eSPI();
    PushButton encoderButton = PushButton(28);
    RotaryEncoder encoder = RotaryEncoder(29, 30);

};

#endif
