#ifndef EnvelopeFollower_h
#define EnvelopeFollower_h

#include <math.h>

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


inline float EnvelopeFollower::process(float in) {
    float v = fabsf(in);
    if (v > env) {
        env = m_a * (env - v) + v;
    } else {
        env = m_r * (env - v) + v;
    }
    return env;
}


#endif
