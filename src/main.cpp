#include "DaisyDuino.h"
#include <RotaryEncoder.h>
#include "MainController.h"
#include "processors/filter/DualFilterController.h"
#include "processors/filterbank/FilterBankController.h"
#include "processors/vowelizer/VowelizerController.h"
#include "processors/vocaltract/TractController.h"
#include "io/PushButton.h"
#include "io/Hardware.h"

DaisyHardware hardware;
size_t numChannels;

Hardware hw;

DualFilterController filterController(hw);
FilterBankController filterBankController(hw);
VowelizerController vowelizerController(hw);
TractController tractController(hw);

#define CONTROLLER_SIZE 4
Controller* controllers[CONTROLLER_SIZE] = {&filterController, &filterBankController, &vowelizerController, &tractController};
MainController mainController(hw, controllers, CONTROLLER_SIZE);


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

    // Initialize Filter, and set parameters.
    vowelizerController.init(sampleRate);
    tractController.init(sampleRate);
    filterController.init(sampleRate);

    DAISY.begin(AudioCallback);

    mainController.init();
}

void loop() {
    mainController.update();
}
