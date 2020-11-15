#ifndef Reverb_h
#define Reverb_h

#include "../../../modules/delays/MultiTapDelay.h"


class Reverb {
    public:
        Reverb() {}
        void init(float sampleRate);
        float process(float in);

    private:

        MultitapDelay multitapDelay;

        int sampleRate;
};

#endif
