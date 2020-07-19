#include "DaisyDuino.h"

DaisyHardware hardware;

size_t num_channels;

Svf filterLeft;
Svf filterRight;

#define LEFT 0
#define RIGHT 1

void AudioCallback(float **in, float **out, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        filterLeft.Process(in[LEFT][i]);
        filterRight.Process(in[RIGHT][i]);

        out[LEFT][i] = filterLeft.Low();
        out[RIGHT][i] = filterRight.High();
    }
}

void setup() {
    float sample_rate;
    // Initialize for Daisy pod at 48kHz
    hardware = DAISY.init(DAISY_SEED, AUDIO_SR_48K);
    num_channels = hardware.num_channels;
    sample_rate = DAISY.get_samplerate();

    // Initialize Filter, and set parameters.
    filterLeft.Init(sample_rate);
    filterLeft.SetFreq(500.0);
    filterLeft.SetRes(0.85);
    filterLeft.SetDrive(0.8);

    filterRight.Init(sample_rate);
    filterRight.SetFreq(500.0);
    filterRight.SetRes(0.85);
    filterRight.SetDrive(0.8);

    DAISY.begin(AudioCallback);
}

void loop() {
}
