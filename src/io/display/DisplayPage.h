#ifndef DisplayPage_h
#define DisplayPage_h

#include "DisplayItem.h"

#define MAX_DISPLAY_ITEMS 5

class DisplayPage {
    public:
        void initTitle(String text, char* shortName);
        void initField(int index, bool selectable);
        void initField(int index, String text, bool selectable);

        void setNumber(int index, uint8_t number);
        void setText(int index, String text);
        void setSelection(int index);
        void nextSelection();

        DisplayItem items[MAX_DISPLAY_ITEMS];
        int size = 1;
        int selectedItem = 0;
};

#endif
