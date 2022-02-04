#ifndef MainController_h
#define MainController_h

#include "Controller.h"
#include <eurorack.h>
#include "apps.h"

#define MAX_CONTROLLERS 20

class MainController : public AbstractMainController<Controller, CONTROLLERS> {
    public:
        MainController();
        void init();
        void update();
        void process(float **in, float **out, size_t size);

        static MainController* mainController;

    private:
        float sampleRate;

        bool pausing = false;
        bool paused = false;

        Timer refreshTimer;

        void cycleController(uint8_t direction);
        void controllerInit();

        void pause() { pausing = true; }
        void hasPaused() { paused = true; }
        void unpause() { paused = false; pausing = false; }

        bool isPausing() { return pausing; }
        bool isPaused() { return paused; }

        void rebootToBootloader();

        static void audioCallback(float **in, float **out, size_t size);
};

#endif