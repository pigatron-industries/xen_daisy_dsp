#ifndef MainController_h
#define MainController_h

#include "Controller.h"
#include "io/Timer.h"

#define MAX_CONTROLLERS 20

class MainController {
    public:
        MainController() {}
        void registerController(Controller* controller);
        void init(float sampleRate);
        void update();
        void process(float **in, float **out, size_t size);

    private:
        float sampleRate;
        int activeController = 0;
        int controllerSize = 0;
        Controller* controllers[MAX_CONTROLLERS];

        Timer refreshTimer;

        UIEvent updateUIEvent();
        void setActiveController(int controllerIndex);

};

#endif