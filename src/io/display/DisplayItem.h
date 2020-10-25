#ifndef DisplayItem_h
#define DisplayItem_h

#include <Arduino.h>

class DisplayItem {
    public:
        uint8_t number;
        String text;
        bool selectable;
        bool dirty = true;
};

#endif
