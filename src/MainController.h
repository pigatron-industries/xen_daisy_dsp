#ifndef MainController_h
#define MainController_h

#include "Controller.h"

class MainController {
    public:
        MainController(Controller** controllers, int size);
        void init(float sampleRate);
        void update();
        void process(float **in, float **out, size_t size);
        void render();

    private:
        int activeController = 0;
        int controllerSize;
        Controller** controllers;

        bool controllerSelectMode = false;

};

#endif