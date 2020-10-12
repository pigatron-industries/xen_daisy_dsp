#ifndef EnvelopeFollower_h
#define EnvelopeFollower_h


class EnvelopeFollower {
    public:
        EnvelopeFollower() {}
        void init(float sampleRate);
        float process(float in);

        void setAttack(float attackMs);
        void setRelease(float releaseMs);

    private:
        float sampleRate;
        float m_a, m_r;
        float env;

};

#endif
