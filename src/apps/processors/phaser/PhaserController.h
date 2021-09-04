#ifndef PhaserController_h
#define PhaserController_h

#include "Controller.h"
#include "modules/delays/AllPassFilter.h"

class PhaserController : public Controller {
    public:
        PhaserController() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        LinearInput<> delayTimeInput = LinearInput<>(HW.A0, -5, 5, 0, 1);
        LinearInput<> feedbackInput = LinearInput<>(HW.A1, -5, 5, 0, 1);
        CrossfadeInput<> dryWetMixInput = CrossfadeInput<>(HW.A2, -5, 5);
        bool invertedFeedback = false;

        AllPassFilter filterLeft;
        AllPassFilter filterRight;

        int sampleRate;
};

#endif
