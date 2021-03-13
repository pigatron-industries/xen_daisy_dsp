#ifndef WaveTablePresets_h
#define WaveTablePresets_h

#include "WaveTable.h"

#define TABLE_SIZE 256

class WaveTablePresets {
    public:
        static WaveTablePresets presets;

        enum WaveformPreset {
            WAVE_SINE,
            WAVE_TRIANGLE,
            WAVE_RAMP,
            WAVE_SQUARE,
            WAVE_IMPULSE,
            WAVE_VIOLIN
        };

        void init(float sampleRate);
        WaveTable* getWaveTable(WaveformPreset waveformPreset);

    private:
        float sampleRate;

        WaveTable sine;
        WaveTable triangle;
        WaveTable ramp;
        WaveTable square;
        WaveTable impulse;
        WaveTable violin;

        void initSine();
        void initTriangle();
        void initRamp();
        void initSquare();
        void initImpulse();
        void initViolin();
};

#endif
