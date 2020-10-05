#include "DaisyDuino.h"
#include "processors/vowelizer/VowelizerController.h"
#include "processors/vocaltract/TractController.h"

DaisyHardware hardware;
size_t numChannels;

VowelizerController vowelizerController;
TractController tractController;


void AudioCallback(float **in, float **out, size_t size) {
    vowelizerController.process(in, out, size);
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

    DAISY.begin(AudioCallback);
}

void loop() {
    vowelizerController.update();
}
