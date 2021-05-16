#ifndef DisplayRenderer_h
#define DisplayRenderer_h

#include "DisplayPage.h"

class DisplayRenderer {
    public:
        virtual void init() = 0;
        virtual void render(DisplayPage* displayedPage, bool all) = 0;
        virtual void alert(char* text) = 0;
};

#endif
