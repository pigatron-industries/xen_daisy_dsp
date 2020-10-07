#ifndef Hardware_h
#define Hardware_h

#include <RotaryEncoder.h>
#include "PushButton.h"
#if defined(XEN_TFT)
    #include <TFT_eSPI.h>
#endif

class Hardware {

public:
    Hardware() {}
    void init();

    PushButton encoderButton = PushButton(28);
    RotaryEncoder encoder = RotaryEncoder(29, 30);
    
    #if defined(XEN_TFT)
        TFT_eSPI tft = TFT_eSPI();
    #endif

};

#endif
