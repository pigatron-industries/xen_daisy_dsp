#include "Display.h"

void Display::init() {
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(1);
}

void Display::setDisplayedPage(DisplayPage* page) {
    displayedPage = page;
    render(true);
}

void Display::render() {
    render(false);
}

void Display::render(bool all) {
    for(int index = 0; index < displayedPage->size; index++) {
        renderItem(index, all);
    }
}

void Display::renderItem(int index, bool all) {
    DisplayItem &item = displayedPage->items[index];
    if(all || item.dirty) {
        Serial.println(index);
        int cursorX = index * LINE_HEIGHT;

        tft.setCursor(LINE_INDENT, cursorX, LINE_FONT);
        if(index == displayedPage->selectedItem) {
            tft.fillRect(0, cursorX, tft.width()-1, LINE_HEIGHT, TFT_NAVY);
            tft.setTextColor(index == 0 ? TFT_YELLOW : TFT_CYAN, TFT_NAVY);
        } else {
            tft.fillRect(0, cursorX, tft.width()-1, LINE_HEIGHT, TFT_BLACK);
            tft.setTextColor(index == 0 ? TFT_OLIVE : TFT_DARKCYAN, TFT_BLACK);
        }

        tft.print(item.text);
        if(index == 0) {
            tft.drawLine(0, cursorX+LINE_HEIGHT-1, tft.width()-1, cursorX+LINE_HEIGHT-1, TFT_OLIVE);
        }

        item.dirty = false;
    }
}