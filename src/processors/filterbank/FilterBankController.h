#ifndef FilterBankController_h
#define FilterBankController_h

#include "../Controller.h"
#include "../../io/AnalogInput.h"

class FilterBankController : public Controller {
    public:
        FilterBankController() {}
        void init(float sampleRate);
        void update();
        void process(float **in, float **out, size_t size);

    private:

};

#endif
