#ifdef XEN_TFT
#include "TFTRenderer.h"

#define LINE_HEIGHT 16
#define LINE_INDENT 2
#define LINE_FONT 2

void TFTRenderer::init() {
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(1);
    tft.setTextWrap(false);
}

void TFTRenderer::render(DisplayPage* displayedPage, bool all) {
    if(all) {
        tft.fillScreen(TFT_BLACK); 
    }

    for(int index = 0; index < displayedPage->size; index++) {
        renderItem(displayedPage, index, all);
    }
}

void TFTRenderer::renderItem(DisplayPage* displayedPage, int index, bool all) {
    DisplayItem &item = displayedPage->items[index];
    if(all || item.dirty) {
        int cursorY = index * LINE_HEIGHT;

        bool selected = index == displayedPage->selectedItem;
        int32_t backgroundColour = selected ? TFT_NAVY : TFT_BLACK;
        int32_t textColour = index == 0 ? 
                                (selected ? TFT_YELLOW : TFT_OLIVE) :
                                (selected ? TFT_CYAN : TFT_DARKCYAN);

        tft.setTextColor(textColour, backgroundColour);
        int16_t textWidth = tft.drawString(item.text, LINE_INDENT, cursorY, LINE_FONT);
        tft.fillRect(0, cursorY, LINE_INDENT, LINE_HEIGHT, backgroundColour);
        tft.fillRect(LINE_INDENT+textWidth, cursorY, tft.width()-1-textWidth-LINE_INDENT, LINE_HEIGHT, backgroundColour);
    
        if(index == 0) {
            tft.drawLine(0, cursorY+LINE_HEIGHT-1, tft.width()-1, cursorY+LINE_HEIGHT-1, TFT_OLIVE);
        }

        item.dirty = false;
    }
}

void TFTRenderer::alert(char* text) {
    //TODO
}

#endif
