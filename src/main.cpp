#include "DaisyDuino.h"
#include "processors/vowelizer/VowelizerProcessor.h"
#include "processors/vocaltract/TractProcessor.h"

DaisyHardware hardware;
size_t numChannels;

VowelizerProcessor vowelizerProcessor;
TractProcessor tractProcessor;


void AudioCallback(float **in, float **out, size_t size) {
    vowelizerProcessor.process(in, out, size);
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
    vowelizerProcessor.init(sampleRate);
    tractProcessor.init(sampleRate);

    DAISY.begin(AudioCallback);
}

void loop() {
    vowelizerProcessor.update();
}
