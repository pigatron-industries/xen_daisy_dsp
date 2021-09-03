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
        void init(int bandCount, PivotPoint pivotPoint, float frequency);
        void init(int bandCount, PivotPoint pivotPoint, float frequency, float pitchInterval);

        void setBandCount(int bandCount);
        
        /* Set either base frequency or centre frequency (depends on pivot point) */ 
        void setFrequency(float frequency);
        /* Set interval between all frequencies */
        void setAllPitchIntervals(float pitchInterval);
        /* Set single pitch interval  */
        void setPitchInterval(int index, float pitchInterval);
        /* Set pitch offset for all frequencies */
        void setPitchOffset(float pitchOffset) { this->pitchOffset = pitchOffset; }

        int getBandCount() { return bandCount; }
        float getFrequency(int index) { return frequencies[index]; }

    protected:
        PivotPoint pivotPoint = PivotPoint::BASE;
        float baseFrequency, centreFrequency;
        int bandCount;
        float pitchOffset;
        float pitches[MAX_BANDS];
        float frequencies[MAX_BANDS];

        void calcBaseFrequency(float centreFrequency, float highPitch);
        void calcFrequency(int index);
};

#endif
