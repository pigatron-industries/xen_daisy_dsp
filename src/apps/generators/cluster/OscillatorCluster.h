#ifndef AdditiveOscillatorController_h
#define AdditiveOscillatorController_h

#include "Controller.h"
#include "io/input/ExpInput.h"
#include "io/input/AnalogInput.h"
#include "modules/wavetable/WaveTableOscillator.h"
#include "modules/wavetable/WaveTable.h"

class OscillatorCluster {
    public:
        OscillatorCluster() {}
        void init(float sampleRate);
        float process();

        void setBaseFrequency(float frequency);
        void setInterval(float interval);

    private:
        static const int MAX_OSCILLATORS = 10;
        WaveTableOscillator oscillators[MAX_OSCILLATORS];
        WaveTable sine;

        float baseFrequency;
        float frequencyMultipliers[MAX_OSCILLATORS];

        void updateFrequencies();
};

#endif
