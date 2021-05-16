#ifdef XEN_ALPHA
#ifndef AlphaRenderer_h
#define AlphaRenderer_h

#include <Adafruit_LEDBackpack.h>
#include "DisplayRenderer.h"

class AlphaRenderer : public DisplayRenderer {
    public:
        virtual void init();
        virtual void render(DisplayPage* displayedPage, bool all);
        virtual void alert(char* text);

    private:
        Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

        void renderItem(DisplayPage* displayedPage, int index, bool all);
};

#endif
#endif