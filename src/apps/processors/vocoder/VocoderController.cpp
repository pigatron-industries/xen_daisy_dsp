#include "VocoderController.h"

#include "modules/wavetable/WaveTableGenerator.h"
#include "modules/wavetable/WaveTablePresets.h"

#define LEFT 0
#define RIGHT 1

#define FIELD_VOCODER_BANDS 1
#define FIELD_VOCODER_FREQUENCYBASE 2
#define FIELD_VOCODER_PITCHINTERVAL 3

void VocoderController::init(float sampleRate) {
    WaveTablePresets::presets.init(sampleRate);

    vocoder.init(sampleRate);
    vocoder.initBandsByCentreFrequency(centreFrequencyInput.getValue(), 0.3333, bands); // 1/3 octave 400 cents
    vocoder.setCarrierOscillator(WaveTablePresets::presets.getWaveTable(WaveTablePresets::WaveformPreset::WAVE_SINE));
    vocoder.setUseCarrierOscillator(true);

    displayPage.initTitle("Vocoder", "VOCO");
    displayPage.initField(FIELD_VOCODER_BANDS, String("Bands: ") + String(bands), true);
    displayPage.initField(FIELD_VOCODER_FREQUENCYBASE, false);
    displayPage.initField(FIELD_VOCODER_PITCHINTERVAL, false);
}

void VocoderController::update() { 
    if(resonanceInput.update()) {
        vocoder.setResonance(resonanceInput.getValue());
    }
    if(stereoMixInput.update()) {
        oddPan.setPan(stereoMixInput.getValue());
        evenPan.setPan(1 - stereoMixInput.getValue());
    }
    centreFrequencyInput.update();
    pitchIntervalInput.update();
    if(centreFrequencyInput.isChanged() || pitchIntervalInput.isChanged()) {
        vocoder.initBandsByCentreFrequency(centreFrequencyInput.getValue(), pitchIntervalInput.getValue(), bands);
    }
}

void VocoderController::updateDisplay() { 
    displayPage.setText(FIELD_VOCODER_FREQUENCYBASE, String("Centre Frequency: ") + String(centreFrequencyInput.getValue(), 0));
    displayPage.setText(FIELD_VOCODER_PITCHINTERVAL, String("Pitch Interval: ") + String(pitchIntervalInput.getValue(), 3));

    // VocoderBand* bands = vocoder.getBands();
    // for(int i = 0; i < vocoder.getBandCount(); i++) {
    //     Serial.print(i);
    //     Serial.print(": ");
    //     Serial.println(bands[i].getFrequency());
    // }
}

void VocoderController::event(UIEvent event, int itemIndex) {
    if(itemIndex > 0) {
        if(event == UIEvent::EVENT_CLOCKWISE) {
            if(bands < MAX_VOCODER_BANDS) {
                bands++;
                vocoder.initBandsByCentreFrequency(centreFrequencyInput.getValue(), pitchIntervalInput.getValue(), bands);
                displayPage.setText(FIELD_VOCODER_BANDS, String("Bands: ") + String(bands));
            }
        } else if (event == UIEvent::EVENT_COUNTERCLOCKWISE) {
            if(bands > MIN_VOCODER_BANDS) {
                bands--;
                vocoder.initBandsByCentreFrequency(centreFrequencyInput.getValue(), pitchIntervalInput.getValue(), bands);
                displayPage.setText(FIELD_VOCODER_BANDS, String("Bands: ") + String(bands));
            }
        }
    }
}

void VocoderController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        vocoder.process(in[LEFT][i], in[RIGHT][i]);
        oddPan.process(vocoder.getEvenOutput());
        evenPan.process(vocoder.getOddOutput());
        out[LEFT][i] = oddPan.getLeftOut() + evenPan.getLeftOut();
        out[RIGHT][i] = oddPan.getRightOut() + evenPan.getRightOut();
    }
}
