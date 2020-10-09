#ifndef DisplayPage_h
#define DisplayPage_h

#include "DisplayItem.h"

#define MAX_DISPLAY_ITEMS 5

class DisplayPage {
    public:
        void initTitle(String text);
        void initField(int index, String text, bool selectable);

        void setText(int index, String text);
        void setSelection(int index);
        void nextSelection();

        DisplayItem items[MAX_DISPLAY_ITEMS];
        int size = 1;
        int selectedItem = -1;
};

#endif
