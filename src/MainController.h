#ifndef MainController_h
#define MainController_h

#include "processors/Controller.h"

class MainController {
    public:
        MainController(Hardware& hardware, Controller** controllers, int size);
        void init(float sampleRate);
        void update();
        void process(float **in, float **out, size_t size);
        void render();

    private:
        Hardware& hw;
        int activeController = 0;
        int controllerSize;
        Controller** controllers;

        bool controllerSelectMode = false;

};

#endif