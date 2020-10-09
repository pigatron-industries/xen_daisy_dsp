#ifndef Controller_h
#define Controller_h

#include "DaisyDuino.h"
#include "io/Hardware.h"
#include "io/display/DisplayPage.h"

#define LINE_HEIGHT 16
#define TEXT_INDENT 2

class Controller {
    public:
        Controller() {}
        char* getName() { return name; }
        DisplayPage* getDisplayPage() { return &displayPage; }

        virtual void init(float sampleRate) = 0;
        virtual void update() {}
        virtual void process(float **in, float **out, size_t size) = 0;

    protected:
        char* name;
        DisplayPage displayPage;
};

#endif
