#include "ClusterController.h"

#include "modules/wavetable/WaveTablePresets.h"

#define LEFT 0
#define RIGHT 1

void ClusterController::init(float sampleRate) {
    oscillatorBank.init(sampleRate, WaveTablePresets::presets.getWaveTable(WaveTablePresets::WaveformPreset::WAVE_SINE), 
                        12, FrequencyBank::PivotPoint::BASE, 100);
    int index = 0;
    for(int octave = 0; octave < 4; octave++) {
        oscillatorBank.getFrequencyBank().setPitchInterval(0, index++, octave);
        oscillatorBank.getFrequencyBank().setPitchInterval(0, index++, octave+0.3219);
        oscillatorBank.getFrequencyBank().setPitchInterval(0, index++, octave+0.5849);
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
    if(frequencyInput.update()) {
        oscillatorBank.getFrequencyBank().setFrequency(frequencyInput.getValue());
        oscillatorBank.updateFrequencies();
    }

    if(interval1Input.update()) {
        oscillatorBank.getFrequencyBank().setPitchInterval(0, 1, 0+interval1Input.getValue());
        oscillatorBank.getFrequencyBank().setPitchInterval(0, 4, 1+interval1Input.getValue());
        oscillatorBank.getFrequencyBank().setPitchInterval(0, 7, 2+interval1Input.getValue());
        oscillatorBank.getFrequencyBank().setPitchInterval(0, 10, 3+interval1Input.getValue());
        oscillatorBank.updateFrequencies();
    }

    if(interval2Input.update()) {
        oscillatorBank.getFrequencyBank().setPitchInterval(0, 2, 0+interval2Input.getValue());
        oscillatorBank.getFrequencyBank().setPitchInterval(0, 5, 1+interval2Input.getValue());
        oscillatorBank.getFrequencyBank().setPitchInterval(0, 8, 2+interval2Input.getValue());
        oscillatorBank.getFrequencyBank().setPitchInterval(0, 11, 3+interval2Input.getValue());
        oscillatorBank.updateFrequencies();
    }
}
