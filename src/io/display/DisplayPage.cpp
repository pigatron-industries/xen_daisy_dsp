#include "DisplayPage.h"
#include "DaisyDuino.h"

#define NO_SELECTION -1

void DisplayPage::initTitle(String text) {
    items[0].text = text;
    items[0].selectable = false;
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
