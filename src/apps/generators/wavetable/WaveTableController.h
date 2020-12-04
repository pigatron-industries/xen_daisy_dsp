#ifndef WaveTableController_h
#define WaveTableController_h

#include "../../../Controller.h"
#include "../../../io/input/PitchInput.h"
#include "WaveTable.h"

class WaveTableController : public Controller {
    public:
        WaveTableController() {}
        virtual void init(float sampleRate);
        virtual void process(float **in, float **out, size_t size);
        virtual void update();

    private:
        PitchInput pitchInput = PitchInput(A0);

        WaveTable wavetable;
};

#endif
