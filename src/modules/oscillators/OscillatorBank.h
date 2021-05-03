#ifndef OscillatorBank_h
#define OscillatorBank_h

#include "modules/frequencybank/InterpolatedFrequencyBank.h"
#include "io/input/ExpInput.h"
#include "io/input/AnalogInput.h"
#include "modules/wavetable/WaveTableOscillator.h"
#include "modules/wavetable/WaveTable.h"
#include "modules/Normalizer.h"

namespace pigatron
{

class OscillatorBank {
    public:
        OscillatorBank() {}
        void init(float sampleRate, WaveTable& wavetable, int bandCount, FrequencyBank::PivotPoint pivotPoint, float frequency);
        void init(float sampleRate, WaveTable& wavetable, int bankCount, int bandCount, FrequencyBank::PivotPoint pivotPoint, float frequency);
        float process();
        
        InterpolatedFrequencyBank& getFrequencyBank() { return frequencyBank; }
        void updateFrequencies();

    private:
        static const int MAX_OSCILLATORS = 20;
        InterpolatedFrequencyBank frequencyBank;
        WaveTableOscillator oscillators[MAX_OSCILLATORS];
        Normalizer normalizer;
};

}

#endif
