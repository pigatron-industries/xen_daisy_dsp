#ifndef Hardware_h
#define Hardware_h

#include <eurorack.h>
#include "display/Display.h"

#define HW Hardware::hw

class Hardware {

public:
    static Hardware hw;
    void init();

    // Native pins
    DigitalInput(0)
    AnalogInput(A0)
    AnalogInput(A1)
    AnalogInput(A2)
    AnalogInput(A3)
    AnalogInput(A4)
    AnalogInput(A5)
    AnalogInput(A6)
    AnalogInput(A7)
    AnalogInput(A8)
    AnalogInput(A9)
    AnalogInput(A10)
    AnalogInput(A11)

    PushButton<> encoderButton = PushButton<>(D0);
    RotaryEncoder encoder = RotaryEncoder(29, 30);
    Display display;

private:
    Hardware() {}
};

#endif
