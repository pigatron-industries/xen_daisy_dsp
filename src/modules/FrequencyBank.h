#ifndef FrequencyBank_h
#define FrequencyBank_h

/**
 * Represents a bank of related frequencies
 */
class FrequencyBank {
    public:
        static const int MAX_BANDS = 30;

        enum PivotPoint {
            BASE,
            CENTRE
        };

        FrequencyBank();
        void init(int bandCount, PivotPoint pivotPoint, float frequency, float pitchInterval);

        void setBandCount(int bandCount);
        void setBaseFrequency(float baseFrequency);
        void setCentreFrequency(float centreFrequency);
        void setAllPitchIntervals(float pitchInterval);
        void setPitchInterval(int index, float pitchInterval);

        int getBandCount() { return bandCount; }
        float getFrequency(int index) { return frequencies[index]; }

    protected:
        PivotPoint pivotPoint = BASE;
        float baseFrequency, centreFrequency;
        int bandCount;
        float pitches[MAX_BANDS];
        float frequencies[MAX_BANDS];

        void calcBaseFrequency(float centreFrequency, float highPitch);
        void calcFrequency(int index);
};

#endif
