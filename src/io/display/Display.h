#ifndef Display_h
#define Display_h

#include "DisplayPage.h"

#if defined(XEN_TFT)
    #include <TFT_eSPI.h>
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
    // void setSelection(int index);
    // void setText(int index, char* text);

private:
    #if defined(XEN_TFT)
        TFT_eSPI tft = TFT_eSPI();
    #endif

    DisplayPage* displayedPage;

    void render(bool all);
    void renderItem(int index, bool all);

};

#endif
