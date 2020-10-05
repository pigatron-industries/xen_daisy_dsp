#include "DaisyDuino.h"
#include <RotaryEncoder.h>
#include "processors/filter/FilterController.h"
#include "processors/vowelizer/VowelizerController.h"
#include "processors/vocaltract/TractController.h"
#include "io/PushButton.h"

DaisyHardware hardware;
size_t numChannels;

PushButton encoderButton(28);
RotaryEncoder encoder(29, 30);

FilterController filterController(encoder);
VowelizerController vowelizerController;
TractController tractController;

enum ModeSelect {
    FILTER,
    VOWELIZER,
    TRACT
};
ModeSelect mode = ModeSelect::FILTER;


void AudioCallback(float **in, float **out, size_t size) {
    switch(mode) {
        case FILTER:
            filterController.process(in, out, size);
            break;
        case VOWELIZER:
            vowelizerController.process(in, out, size);
            break;
        case TRACT:
            tractController.process(in, out, size);
            break;
    }
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
}

void loop() {
    encoder.tick();
    if(encoderButton.update()) {
        if(encoderButton.released()) {
            mode = static_cast<ModeSelect>((mode + 1) % (ModeSelect::TRACT + 1));
            Serial.println(mode);
        }
    }

    switch(mode) {
        case FILTER:
            filterController.update();
            break;
        case VOWELIZER:
            vowelizerController.update();
            break;
        case TRACT:
            tractController.update();
            break;
    }
}
