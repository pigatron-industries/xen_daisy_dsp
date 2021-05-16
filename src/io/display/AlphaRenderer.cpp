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
        //if(index == 0) {
            alpha4.writeDigitAscii(0, item.shortName[0], index == 0);
            alpha4.writeDigitAscii(1, item.shortName[1], index == 1);
            alpha4.writeDigitAscii(2, item.shortName[2], index == 2);
            alpha4.writeDigitAscii(3, item.shortName[3], index == 3);
        //}
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