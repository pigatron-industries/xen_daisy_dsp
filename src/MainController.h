#ifndef MainController_h
#define MainController_h

#include "Controller.h"

#define MAX_CONTROLLERS 20

class MainController {
    public:
        static MainController instance;
        static void audioCallback(float **in, float **out, size_t size);

        MainController() {}
        void registerController(Controller* controller);
        void init();
        void update();
        void process(float **in, float **out, size_t size);

    private:
        float sampleRate;
        int activeController = 0;
        int controllerSize = 0;
        Controller* controllers[MAX_CONTROLLERS];

        bool pausing = false;
        bool paused = false;

        Timer refreshTimer;

        UIEvent updateUIEvent();
        void setActiveController(int controllerIndex);

        void pause() { pausing = true; }
        void hasPaused() { paused = true; }
        void unpause() { paused = false; pausing = false; }

        bool isPausing() { return pausing; }
        bool isPaused() { return paused; }

        void rebootToBootloader();
};

#endif