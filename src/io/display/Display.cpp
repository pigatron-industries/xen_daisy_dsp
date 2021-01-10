#include "Display.h"
#include <SoftwareSerial.h>

#define SEG_CLEAR_DISPLAY 0x76
#define SEG_DECIMAL_CONTROL 0x77
#define SEG_CURSOR_CONTROL 0x79
#define SEG_BAUD_CONTROL 0x7F

#define SEG_DECIMAL_1     0b00000001
#define SEG_DECIMAL_2     0b00000010
#define SEG_DECIMAL_3     0b00000100
#define SEG_DECIMAL_4     0b00001000
#define SEG_DECIMAL_COLON 0b00010000
#define SEG_DECIMAL_APOST 0b00100000

void Display::init() {
    #if defined(XEN_TFT)
        tft.init();
        tft.setRotation(3);
        tft.fillScreen(TFT_BLACK);
        tft.setTextSize(1);
        tft.setTextWrap(false);
    #endif
    #if defined(XEN_ALPHA)
        alpha4.begin(0x70);
        alpha4.setBrightness(10);
    #endif
    #if defined(XEN_7SEG)
        Serial1.begin(9600);
        Serial1.write(SEG_BAUD_CONTROL);
        Serial1.write(0x04);

        Serial1.end();
        Serial1.begin(19200);
        Serial1.write(SEG_CLEAR_DISPLAY);
        Serial1.write(0x7A);  // Set brightness command byte
        Serial1.write(0xFF);  // brightness data byte
    #endif
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
        #if defined(XEN_TFT)
            tft.fillScreen(TFT_BLACK); 
        #endif
        #if defined(XEN_7SEG)        
            Serial1.write(SEG_CLEAR_DISPLAY);
        #endif
    }

    for(int index = 0; index < displayedPage->size; index++) {
        renderItem(index, all);
    }
}

#if defined(XEN_TFT)
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
#endif

#if defined(XEN_ALPHA)
    void Display::renderItem(int index, bool all) {
        DisplayItem &item = displayedPage->items[index];
        if(all || item.dirty) {
            bool selected = index == displayedPage->selectedItem;
            if(index == 0) {
                alpha4.writeDigitAscii(0, item.shortName[0]);
                alpha4.writeDigitAscii(1, item.shortName[1]);
                alpha4.writeDigitAscii(2, item.shortName[2]);
                alpha4.writeDigitAscii(3, item.shortName[3]);
                alpha4.writeDisplay();
            }
        }
    }
#endif

#if defined(XEN_7SEG)
    void Display::renderItem(int index, bool all) {
        DisplayItem &item = displayedPage->items[index];
        if(all || item.dirty) {
            bool selected = index == displayedPage->selectedItem;
            uint8_t decimalFlags = SEG_DECIMAL_COLON;
            // First 2 digits app number
            if(index == 0) {
                Serial1.write(SEG_CURSOR_CONTROL);
                Serial1.write(0x00);
                Serial1.write(item.number >> 4);
                Serial1.write(SEG_CURSOR_CONTROL);
                Serial1.write(0x01);
                Serial1.write(item.number);
                if(selected) {
                    decimalFlags |= SEG_DECIMAL_1;
                }
            }

            Serial1.write(SEG_DECIMAL_CONTROL);
            Serial1.write(decimalFlags);
        }
    }
#endif

