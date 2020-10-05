#ifndef Controller_h
#define Controller_h

#include "DaisyDuino.h"

class Controller {
    public:
        Controller() {}
        void init(float sampleRate);
        void update();
        void process(float **in, float **out, size_t size);

};

#endif
