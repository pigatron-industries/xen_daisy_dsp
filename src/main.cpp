#include "DaisyDuino.h"
#include <RotaryEncoder.h>
#include "MainController.h"
#include "io/Hardware.h"

Hardware hw;
DaisyHardware hardware;
size_t numChannels;

#if defined(XEN_DUAL_FILTER)
    #include "processors/filter/DualFilterController.h"
    DualFilterController filterController(hw);
#endif
#if defined(XEN_FILTER_BANK)
    #include "processors/filterbank/FilterBankController.h"
    FilterBankController filterBankController(hw);
#endif
#if defined(XEN_VOWEL_FILTER)
    #include "processors/vowelizer/VowelizerController.h"
    VowelizerController vowelizerController(hw);
#endif
#if defined(XEN_VOCAL_TRACT)
    #include "processors/vocaltract/TractController.h"
    TractController tractController(hw);
#endif

Controller* controllers[XEN_CONTROLLER_COUNT] = {
    #if defined(XEN_DUAL_FILTER)
        &filterController,
    #endif
    #if defined(XEN_FILTER_BANK)
        &filterBankController, 
    #endif
    #if defined(XEN_VOWEL_FILTER)
        &vowelizerController, 
    #endif
    #if defined(XEN_VOCAL_TRACT)
        &tractController
    #endif
};
MainController mainController(hw, controllers, XEN_CONTROLLER_COUNT);


void AudioCallback(float **in, float **out, size_t size) {
    mainController.process(in, out, size);
}

void setup() {
    Serial.begin(115200);
    Serial.println("Pigatron Industries");

    float sampleRate;
    // Initialize for Daisy pod at 48kHz
    hardware = DAISY.init(DAISY_SEED, AUDIO_SR_48K);
    numChannels = hardware.num_channels;
    sampleRate = DAISY.get_samplerate();

    mainController.init(sampleRate);

    DAISY.begin(AudioCallback);
}

void loop() {
    mainController.update();
}
