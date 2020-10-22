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

MainController mainController;

void AudioCallback(float **in, float **out, size_t size) {
    mainController.process(in, out, size);
}

void setup() {
    Serial.begin(115200);
    Serial.println("Pigatron Industries");

    #if defined(XEN_OSCILLATOR)
        mainController.registerController(&oscillatorController);
    #endif
    #if defined(XEN_DUAL_FILTER)
        mainController.registerController(&dualFilterController);
    #endif
    #if defined(XEN_FILTER_BANK)
        mainController.registerController(&filterBankController);
    #endif
    #if defined(XEN_VOWEL_FILTER)
        mainController.registerController(&vowelizerController);
    #endif
    #if defined(XEN_VOCODER)
        mainController.registerController(&vocoderController);
    #endif
    #if defined(XEN_VOCAL_TRACT)
        mainController.registerController(&tractController);
    #endif
    #if defined(XEN_FLANGER)
        mainController.registerController(&flangerController);
    #endif
    #if defined(XEN_SPATIALIZER)
        mainController.registerController(&spatializerController);
    #endif
    #if defined(XEN_GLOTTIS)
        mainController.registerController(&glottisController);
    #endif
    #if defined(XEN_FREQUENCYANALYSER)
        mainController.registerController(&frequencyController);
    #endif

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
