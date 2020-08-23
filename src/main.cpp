#include "DaisyDuino.h"
#include "io/PitchInput.h"
#include "io/AnalogInput.h"
#include "modules/Vocalizer.h"

DaisyHardware hardware;

size_t num_channels;

Vocalizer vocalizer;
AnalogInput rangeInput(A0, -5, 5, 0, 5);
AnalogInput vowelInput(A1, -5, 5, 0, 5);
AnalogInput pitchInput(A2, -5, 5, 1, 2);


#define LEFT 0
#define RIGHT 1

void AudioCallback(float **in, float **out, size_t size)
{
    vocalizer.setVowelAndRange(vowelInput.getVirtualValue(), rangeInput.getVirtualValue());
    vocalizer.setPitch(pitchInput.getVirtualValue());

    for (size_t i = 0; i < size; i++) {
        out[LEFT][i] = vocalizer.process(in[LEFT][i]);
    }
}

void setup() {
    Serial.begin(115200);
    Serial.println("Pigatron Industries");

    float sample_rate;
    // Initialize for Daisy pod at 48kHz
    hardware = DAISY.init(DAISY_SEED, AUDIO_SR_48K);
    num_channels = hardware.num_channels;
    sample_rate = DAISY.get_samplerate();

    // Initialize Filter, and set parameters.
    vocalizer.init(sample_rate);

    DAISY.begin(AudioCallback);
}

void loop() {
    rangeInput.update();
    vowelInput.update();
    pitchInput.update();
}
