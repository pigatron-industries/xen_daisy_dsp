#ifdef XEN_TFT
#ifndef TFTRenderer_h
#define TFTRenderer_h

#include <TFT_eSPI.h>
#include "DisplayRenderer.h"

class TFTRenderer : public DisplayRenderer {
    public:
        virtual void init();
        virtual void render(DisplayPage* displayedPage, bool all);
        virtual void alert(char* text);

    private:
        TFT_eSPI tft = TFT_eSPI();

        void renderItem(DisplayPage* displayedPage, int index, bool all);
};

#endif
#endif