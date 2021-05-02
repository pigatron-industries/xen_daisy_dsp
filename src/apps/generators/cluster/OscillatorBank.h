#ifndef OscillatorBank_h
#define OscillatorBank_h

#include "modules/FrequencyBank.h"
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
        void init(float sampleRate, WaveTable& wavetable, int bandCount, FrequencyBank::PivotPoint pivotPoint, float frequency, float pitchInterval);
        float process();
        
        void setBaseFrequency(float frequency) { frequencyBank.setBaseFrequency(frequency); updateFrequencies(); }
        void setPitchInterval(int index, float interval) { frequencyBank.setPitchInterval(index, interval); updateFrequencies(); }
        void setAllPitchIntervals(float interval) { frequencyBank.setAllPitchIntervals(interval); updateFrequencies(); }

    private:
        static const int MAX_OSCILLATORS = 20;
        FrequencyBank frequencyBank;
        WaveTableOscillator oscillators[MAX_OSCILLATORS];
        Normalizer normalizer;

        void updateFrequencies();
};

}

#endif
