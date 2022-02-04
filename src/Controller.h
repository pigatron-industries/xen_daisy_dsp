#ifndef Controller_h
#define Controller_h

#include "io/Hardware.h"
#include "io/display/DisplayPage.h"
#include <eurorack.h>

#define LINE_HEIGHT 16
#define TEXT_INDENT 2

class Controller : public AbstractController {
    public:
        Controller() {}
        char* getName() { return name; }
        DisplayPage* getDisplayPage() { return &displayPage; }

        virtual void init(float sampleRate) {}
        virtual void init() {}
        virtual void update() {}
        virtual void updateDisplay() {}
        virtual void event(RotaryEncoderButton::EncoderEvent event, int itemIndex) {}
        virtual void process(float **in, float **out, size_t size) = 0;

    protected:
        char* name;
        DisplayPage displayPage;
};

#endif
