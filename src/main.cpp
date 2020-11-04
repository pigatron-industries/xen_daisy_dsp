#include "DaisyDuino.h"
#include <RotaryEncoder.h>
#include "MainController.h"
#include "io/Hardware.h"
#include "apps.h"

DaisyHardware hardware;
size_t numChannels;

void setup() {
    Serial.begin(115200);
    Serial.println("Pigatron Industries");

    registerApps();

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
