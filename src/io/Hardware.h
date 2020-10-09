#ifndef Hardware_h
#define Hardware_h

#include <RotaryEncoder.h>
#include "PushButton.h"
#include "display/Display.h"

class Hardware {

public:
    static Hardware hw;
    void init();

    PushButton encoderButton = PushButton(28);
    RotaryEncoder encoder = RotaryEncoder(29, 30);
    Display display;

private:
    Hardware() {}
};

#endif
