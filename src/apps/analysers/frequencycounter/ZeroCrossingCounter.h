#ifndef ZeroCrossingCounter_h
#define ZeroCrossingCounter_h

enum Sign {
    POSITIVE,
    NEGATIVE
};

class ZeroCrossingCounter {
    public:
        ZeroCrossingCounter() {}
        void init(float sampleRate);
        void process(float in);

        float getFrequency();

    private:
        float sampleRate;
        float sampleRateRecip;

        Sign lastSign;
        int sampleCount;

        int timeSamples;
        float time;
        float smoothedTime;

};


#endif