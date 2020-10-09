#ifndef DisplayItem_h
#define DisplayItem_h

#include <Arduino.h>

class DisplayItem {
    public:
        String text;
        bool selectable;
        bool dirty = true;
};

#endif
