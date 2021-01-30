#ifndef AllPass_h
#define AllPass_h

class AllPass {
    public:
        AllPass() {}
        void init(float sampleRate);
        float process(float in);

        void setGain(float gain);
        void setFrequency(float frequency);


    private:

        float sampleRate;

        float frequency;
        float gain;
        float coefficient;

        float buffer;

        void calcCoefficient();
};

inline float AllPass::process(float in) {
    // float xh = in - coefficient * buffer;
    // float out = coefficient * xh + buffer;
    // buffer = xh;
    float out = buffer + coefficient * in;
    buffer = in - coefficient * out;
    return out;
}

#endif
