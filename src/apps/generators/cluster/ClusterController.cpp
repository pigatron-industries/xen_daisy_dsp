#include "ClusterController.h"

#include "modules/wavetable/WaveTablePresets.h"

#define LEFT 0
#define RIGHT 1

void ClusterController::init(float sampleRate) {
    oscillatorBank.init(sampleRate, WaveTablePresets::presets.getWaveTable(WaveTablePresets::WaveformPreset::WAVE_SINE), 
                        10, FrequencyBank::PivotPoint::CENTRE, 100);
    int index = 0;
    for(int octave = 0; octave < 4; octave++) {
        oscillatorBank.getFrequencyBank().setAllPitchIntervals(0, 1);
        oscillatorBank.getFrequencyBank().setFrequency(centreFrequencyInput.getValue());
    }

    displayPage.initTitle("Cluster", "CLST");
}

void ClusterController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        out[LEFT][i] = oscillatorBank.process();
        out[RIGHT][i] = out[LEFT][i];
    }
}

void ClusterController::update() {
    if(centreFrequencyInput.update()) {
        oscillatorBank.getFrequencyBank().setFrequency(centreFrequencyInput.getValue());
        oscillatorBank.updateFrequencies();
    }

    if(intervalInput.update()) {
        oscillatorBank.getFrequencyBank().setAllPitchIntervals(0, intervalInput.getValue());
        oscillatorBank.updateFrequencies();
    }

    if(offsetIntervalInput.update()) {
        oscillatorBank.getFrequencyBank().setPitchOffset(0, offsetIntervalInput.getValue());
        oscillatorBank.updateFrequencies();
    }
}
