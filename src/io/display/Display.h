#ifndef Display_h
#define Display_h

#include "DisplayPage.h"
#include "../Timer.h"

#if defined(XEN_TFT)
    #include <TFT_eSPI.h>
#endif
#if defined(XEN_ALPHA)
    #include <Adafruit_LEDBackpack.h>
#endif

#define LINE_HEIGHT 16
#define LINE_INDENT 2
#define LINE_FONT 2

class Display {

public:
    Display() {}
    void init();
    void setDisplayedPage(DisplayPage* page);
    void render();
    void prog();
    
private:
    #if defined(XEN_TFT)
        TFT_eSPI tft = TFT_eSPI();
    #endif
    #if defined(XEN_ALPHA)
        Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();
    #endif

    DisplayPage* displayedPage;

    void render(bool all);
    void renderItem(int index, bool all);

};

#endif
