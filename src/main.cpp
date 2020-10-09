#include "DaisyDuino.h"
#include <RotaryEncoder.h>
#include "MainController.h"
#include "io/Hardware.h"

DaisyHardware hardware;
size_t numChannels;

#if defined(XEN_DUAL_FILTER)
    #include "apps/processors/filter/DualFilterController.h"
    DualFilterController filterController;
#endif
#if defined(XEN_FILTER_BANK)
    #include "apps/processors/filterbank/FilterBankController.h"
    FilterBankController filterBankController;
#endif
#if defined(XEN_VOWEL_FILTER)
    #include "apps/processors/vowelizer/VowelizerController.h"
    VowelizerController vowelizerController;
#endif
#if defined(XEN_VOCAL_TRACT)
    #include "apps/processors/vocaltract/TractController.h"
    TractController tractController;
#endif
#if defined(XEN_FLANGER)
    #include "apps/processors/flanger/FlangerController.h"
    FlangerController flangerController;
#endif
#if defined(XEN_GLOTTIS)
    #include "apps/generators/glottis/GlottisController.h"
    GlottisController glottisController;
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
        &tractController,
    #endif
    #if defined(XEN_FLANGER)
        &flangerController,
    #endif
    #if defined(XEN_GLOTTIS)
        &glottisController,
    #endif
};
MainController mainController(controllers, XEN_CONTROLLER_COUNT);


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
