#ifndef Hardware_h
#define Hardware_h

#include <eurorack.h>
#include "display/Display.h"

#define HW Hardware::hw

#define SDRAM_TOTAL_SIZE (16*1024*1024)
#define SDRAM_PERM_SIZE (256*1024)
#define SDRAM_TEMP_SIZE SDRAM_TOTAL_SIZE-SDRAM_PERM_SIZE

class Hardware {

public:
    static Hardware hw;
    void init();

    // Memory pool
    static float permMemBuffer[SDRAM_PERM_SIZE];
    static float tempMemBuffer[SDRAM_TEMP_SIZE];
    MemPool<float> permPool = MemPool<float>(Hardware::permMemBuffer, SDRAM_PERM_SIZE);
    MemPool<float> tempPool = MemPool<float>(Hardware::tempMemBuffer, SDRAM_TEMP_SIZE);

    // Native pins
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

    RotaryEncoderButton rotaryEncoderButton = RotaryEncoderButton(29, 30, 0);
    Display display;

private:
    Hardware() {}
};

#endif
