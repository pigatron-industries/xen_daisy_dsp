#ifndef Controller_h
#define Controller_h

#include "io/Hardware.h"
#include "io/display/DisplayPage.h"

#define LINE_HEIGHT 16
#define TEXT_INDENT 2

enum UIEvent {
    EVENT_NONE,
    EVENT_CLOCKWISE,
    EVENT_COUNTERCLOCKWISE,
    EVENT_SHORT_PRESS,
    EVENT_LONG_PRESS
};

class Controller {
    public:
        Controller() {}
        char* getName() { return name; }
        DisplayPage* getDisplayPage() { return &displayPage; }

        virtual void firstInit(float sampleRate) { firstInitCalled = true; };
        virtual void init(float sampleRate) { if(!firstInitCalled) { this->firstInit(sampleRate); } };
        virtual void update() {}
        virtual void updateDisplay() {}
        virtual void event(UIEvent event, int itemIndex) {}
        virtual void process(float **in, float **out, size_t size) = 0;

    protected:
        char* name;
        DisplayPage displayPage;
        bool firstInitCalled = false;
};

#endif
