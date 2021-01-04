#ifndef Normalizer_h
#define Normalizer_h

class Normalizer {
    public:
        Normalizer() {}
        void init(int sampleSize, float targetAmplitude, float maxGain);
        float process(float in);

        float getGain() { return gain; }

    private:
        int sampleSize;
        float maxGain;
        float targetAmplitude;

        int sampleCounter;
        float maxSample;
        float gain;
};

#endif
