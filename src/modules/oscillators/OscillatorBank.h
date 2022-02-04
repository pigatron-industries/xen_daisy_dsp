#ifndef OscillatorBank_h
#define OscillatorBank_h

#include "modules/frequencybank/InterpolatedFrequencyBank.h"
#include "modules/wavetable/WaveTableOscillator.h"
#include "modules/wavetable/WaveTable.h"
#include "modules/Normalizer.h"

namespace pigatron
{
class [[deprecated]] OscillatorBank {
    public:
        OscillatorBank() {}
        void init(float sampleRate, WaveTable& wavetable, int bandCount, FrequencyBank::PivotPoint pivotPoint, float frequency);
        void init(float sampleRate, WaveTable& wavetable, int bankCount, int bandCount, FrequencyBank::PivotPoint pivotPoint, float frequency);
        float process();

        void setAmplitude(int bandIndex, float amplitude);
        
        InterpolatedFrequencyBank& getFrequencyBank() { return frequencyBank; }
        void updateFrequencies();

    private:
        static const int MAX_OSCILLATORS = 20;
        InterpolatedFrequencyBank frequencyBank;
        WaveTableOscillator oscillators[MAX_OSCILLATORS];
        float amplitudes[MAX_OSCILLATORS];
};

}

#endif
