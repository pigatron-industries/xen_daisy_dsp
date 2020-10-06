#ifndef Controller_h
#define Controller_h

#include "DaisyDuino.h"
#include "../io/Hardware.h"

#define LINE_HEIGHT 16
#define TEXT_INDENT 2

class Controller {
    public:
        Controller(Hardware& hardware, char* name) : hw(hardware) { this->name = name; }
        char* getName() { return name; }
        virtual void init(float sampleRate) = 0;
        virtual void update() = 0;
        virtual void process(float **in, float **out, size_t size) = 0;
        virtual void render() = 0;

    protected:
        Hardware& hw;
        char* name;
};

#endif
