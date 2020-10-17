#include "EnvelopeFollower.h"

#include <math.h>

void EnvelopeFollower::init(float sampleRate) {
    this->sampleRate = sampleRate;
    setAttack(10);
    setRelease(10);
}

void EnvelopeFollower::setAttack(float attackMs) {
    m_a = pow (0.01, 1.0 / (attackMs * sampleRate * 0.001));
}

void EnvelopeFollower::setRelease(float releaseMs) {
    m_r = pow (0.01, 1.0 / (releaseMs * sampleRate * 0.001));
}
