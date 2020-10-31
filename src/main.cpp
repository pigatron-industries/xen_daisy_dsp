#include "DaisyDuino.h"
#include <RotaryEncoder.h>
#include "MainController.h"
#include "io/Hardware.h"

DaisyHardware hardware;
size_t numChannels;

#if defined(XEN_OSCILLATOR)
    #include "apps/generators/oscillator/OscillatorController.h"
    OscillatorController oscillatorController;
#endif
#if defined(XEN_DUAL_FILTER)
    #include "apps/processors/filter/DualFilterController.h"
    DualFilterController dualFilterController;
#endif
#if defined(XEN_FILTER_BANK)
    #include "apps/processors/filterbank/FilterBankController.h"
    FilterBankController filterBankController;
#endif
#if defined(XEN_VOCODER)
    #include "apps/processors/vocoder/VocoderController.h"
    VocoderController vocoderController;
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
#if defined(XEN_REVERB)
    #include "apps/processors/reverb/ReverbController.h"
    ReverbController reverbController;
#endif
#if defined(XEN_SPATIALIZER)
    #include "apps/processors/spatializer/SpatializerController.h"
    SpatializerController spatializerController;
#endif
#if defined(XEN_GLOTTIS)
    #include "apps/generators/glottis/GlottisController.h"
    GlottisController glottisController;
#endif
#if defined(XEN_FREQUENCYANALYSER)
    #include "apps/analysers/frequencyanalyser/FrequencyController.h"
    FrequencyController frequencyController;
#endif

void setup() {
    Serial.begin(115200);
    Serial.println("Pigatron Industries");

    #if defined(XEN_OSCILLATOR)
        MainController::instance.registerController(&oscillatorController);
    #endif
    #if defined(XEN_DUAL_FILTER)
        MainController::instance.registerController(&dualFilterController);
    #endif
    #if defined(XEN_FILTER_BANK)
        MainController::instance.registerController(&filterBankController);
    #endif
    #if defined(XEN_VOWEL_FILTER)
        MainController::instance.registerController(&vowelizerController);
    #endif
    #if defined(XEN_VOCODER)
        MainController::instance.registerController(&vocoderController);
    #endif
    #if defined(XEN_VOCAL_TRACT)
        MainController::instance.registerController(&tractController);
    #endif
    #if defined(XEN_REVERB)
        MainController::instance.registerController(&reverbController);
    #endif
    #if defined(XEN_FLANGER)
        MainController::instance.registerController(&flangerController);
    #endif
    #if defined(XEN_SPATIALIZER)
        MainController::instance.registerController(&spatializerController);
    #endif
    #if defined(XEN_GLOTTIS)
        MainController::instance.registerController(&glottisController);
    #endif
    #if defined(XEN_FREQUENCYANALYSER)
        MainController::instance.registerController(&frequencyController);
    #endif

    float sampleRate;
    // Initialize for Daisy pod at 48kHz
    hardware = DAISY.init(DAISY_SEED, AUDIO_SR_48K);
    numChannels = hardware.num_channels;
    sampleRate = DAISY.get_samplerate();

    MainController::instance.init(sampleRate);
}

void loop() {
    MainController::instance.update();
}
