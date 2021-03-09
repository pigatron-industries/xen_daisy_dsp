#include "DisplayPage.h"

#define NO_SELECTION -1

void DisplayPage::initTitle(String text, char* shortName) {
    items[0].text = text;
    items[0].selectable = false;
    items[0].shortName[0] = shortName[0];
    items[0].shortName[1] = shortName[1];
    items[0].shortName[2] = shortName[2];
    items[0].shortName[3] = shortName[3];
}

void DisplayPage::initField(int index, bool selectable) {
    if(index >= size) size = index+1;
    items[index].text = String("");
    items[index].selectable = selectable;
}

void DisplayPage::initField(int index, String text, bool selectable) {
    if(index >= size) size = index+1;
    items[index].text = text;
    items[index].selectable = selectable;
}

void DisplayPage::setNumber(int index, uint8_t number) {
    items[index].number = number;
    items[index].dirty = true;
}

void DisplayPage::setText(int index, String text) {
    items[index].text = text;
    items[index].dirty = true;
}

void DisplayPage::setSelection(int index) {
    if(selectedItem != NO_SELECTION) {
        items[selectedItem].dirty = true;
    }
    selectedItem = index;
    if(selectedItem != NO_SELECTION) {
        items[selectedItem].dirty = true;
    }
}

void DisplayPage::nextSelection() {
    if(selectedItem != NO_SELECTION) {
        items[selectedItem].dirty = true;
    }

    bool itemFound = false;
    for(int i = selectedItem+1; i < size; i++) {
        if(items[i].selectable) {
            selectedItem = i;
            items[selectedItem].dirty = true;
            itemFound = true;
            break;
        }
    }

    if(!itemFound) {
        selectedItem = NO_SELECTION;
    }
}
