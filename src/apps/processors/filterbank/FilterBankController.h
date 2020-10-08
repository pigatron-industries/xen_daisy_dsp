#ifndef FilterBankController_h
#define FilterBankController_h

#include "FilterBank.h"
#include "../../../Controller.h"
#include "../../../io/AnalogInput.h"

class FilterBankController : public Controller {
    public:
        FilterBankController(Hardware& hardware) : Controller(hardware, "Filter Bank") {}
        virtual void init(float sampleRate);
        virtual void update();
        virtual void process(float **in, float **out, size_t size);
        virtual void render();

    private:
        FilterBank filterBank;

};

#endif
