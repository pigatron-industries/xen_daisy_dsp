#include "Display.h"


void Display::init() {
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(1);
    tft.setTextWrap(false);
}

void Display::setDisplayedPage(DisplayPage* page) {
    displayedPage = page;
    render(true);
}

void Display::render() {
    render(false);
}

void Display::render(bool all) {
    if(all) {
        tft.fillScreen(TFT_BLACK); 
    }
    for(int index = 0; index < displayedPage->size; index++) {
        renderItem(index, all);
    }
}

void Display::renderItem(int index, bool all) {
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