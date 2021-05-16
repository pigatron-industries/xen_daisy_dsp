#ifdef XEN_ALPHA
#include "AlphaRenderer.h"

void AlphaRenderer::init() {
    alpha4.begin(0x70);
    alpha4.setBrightness(10);
}

void AlphaRenderer::render(DisplayPage* displayedPage, bool all) {

    for(int index = 0; index < displayedPage->size; index++) {
        renderItem(displayedPage, index, all);
    }

    alpha4.writeDisplay();
}

void AlphaRenderer::renderItem(DisplayPage* displayedPage, int index, bool all) {
    DisplayItem &item = displayedPage->items[index];
    if(all || item.dirty) {
        bool selected = index == displayedPage->selectedItem;
        if(selected) {
            if(item.type == DisplayItem::Type::TEXT) {
                alpha4.writeDigitAscii(0, item.shortName[0], displayedPage->selectedItem == 0);
                alpha4.writeDigitAscii(1, item.shortName[1], displayedPage->selectedItem == 1);
                alpha4.writeDigitAscii(2, item.shortName[2], displayedPage->selectedItem == 2);
                alpha4.writeDigitAscii(3, item.shortName[3], displayedPage->selectedItem == 3);
            } else {
                char numtext[5];
                sprintf(numtext, "%04d", item.number);
                alpha4.writeDigitAscii(0, numtext[0], displayedPage->selectedItem == 0);
                alpha4.writeDigitAscii(1, numtext[1], displayedPage->selectedItem == 1);
                alpha4.writeDigitAscii(2, numtext[2], displayedPage->selectedItem == 2);
                alpha4.writeDigitAscii(3, numtext[3], displayedPage->selectedItem == 3);
            }
        }
    }
}

void AlphaRenderer::alert(char* text) {
    alpha4.writeDigitAscii(0, 'P');
    alpha4.writeDigitAscii(1, 'R');
    alpha4.writeDigitAscii(2, 'O');
    alpha4.writeDigitAscii(3, 'G');
    alpha4.writeDisplay();
}

#endif