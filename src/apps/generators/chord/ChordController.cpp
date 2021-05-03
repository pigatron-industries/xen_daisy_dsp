#include "ChordController.h"

#include "modules/wavetable/WaveTablePresets.h"

#define LEFT 0
#define RIGHT 1

void ChordController::init(float sampleRate) {
    oscillatorBank.init(sampleRate, WaveTablePresets::presets.getWaveTable(WaveTablePresets::WaveformPreset::WAVE_SINE), 
                        2, 12, FrequencyBank::PivotPoint::BASE, 100);

    for(int octave = 0, bandIndex = 0; octave < 4; octave++) {
        oscillatorBank.getFrequencyBank().setPitchInterval(0, bandIndex++, octave);
        oscillatorBank.getFrequencyBank().setPitchInterval(0, bandIndex++, octave+0.3333);
        oscillatorBank.getFrequencyBank().setPitchInterval(0, bandIndex++, octave+0.5849);
    }

    for(int octave = 0, bandIndex = 0; octave < 4; octave++) {
        oscillatorBank.getFrequencyBank().setPitchInterval(1, bandIndex++, octave);
        oscillatorBank.getFrequencyBank().setPitchInterval(1, bandIndex++, octave+0.25);
        oscillatorBank.getFrequencyBank().setPitchInterval(1, bandIndex++, octave+0.5849);
    }

    displayPage.initTitle("Chord", "CHRD");
}

void ChordController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        out[LEFT][i] = oscillatorBank.process();
        out[RIGHT][i] = out[LEFT][i];
    }
}

void ChordController::update() {
    if(frequencyInput.update()) {
        oscillatorBank.getFrequencyBank().setFrequency(frequencyInput.getValue());
        oscillatorBank.updateFrequencies();
    }
    if(chordInput.update()) {
        oscillatorBank.getFrequencyBank().setInterpolation(chordInput.getValue());
        oscillatorBank.updateFrequencies();
    }
}
