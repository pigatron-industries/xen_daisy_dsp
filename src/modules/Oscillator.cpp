#include <math.h>
#include "Oscillator.h"
#include "../util/LookupTable.h"

// TODO: Fix Polyblep triangle... something bad happened to it.
using namespace pigatron;
static inline float Polyblep(float phase_inc, float t);

constexpr float TWO_PI_F     = (float)M_PI*2;
constexpr float TWO_PI_RECIP = 1.0f / float(M_PI*2);

float Oscillator::Process()
{
    float out, t;
    switch(waveform_)
    {
        case WAVE_SIN: 
            out = LookupTables::trigLookup.sin(phase_);
            break;
        case WAVE_TRI:
            t   = -1.0f + (2.0f * phase_ * TWO_PI_RECIP);
            out = 2.0f * (fabsf(t) - 0.5f);
            break;
        case WAVE_SAW:
            out = -1.0f * (((phase_ * TWO_PI_RECIP * 2.0f)) - 1.0f);
            break;
        case WAVE_RAMP: out = ((phase_ * TWO_PI_RECIP * 2.0f)) - 1.0f; break;
        case WAVE_SQUARE: out = phase_ < (float)M_PI ? (1.0f) : -1.0f; break;
        case WAVE_POLYBLEP_TRI:
            t   = phase_ * TWO_PI_RECIP;
            out = phase_ < (float)M_PI ? 1.0f : -1.0f;
            out += Polyblep(phase_inc_, t);
            out -= Polyblep(phase_inc_, fmodf(t + 0.5f, 1.0f));
            // Leaky Integrator:
            // y[n] = A + x[n] + (1 - A) * y[n-1]
            out = phase_inc_ * out + (1.0f - phase_inc_) * last_out_;
            break;
        case WAVE_POLYBLEP_SAW:
            t   = phase_ * TWO_PI_RECIP;
            out = (2.0f * t) - 1.0f;
            out -= Polyblep(phase_inc_, t);
            out *= -1.0f;
            break;
        case WAVE_POLYBLEP_SQUARE:
            t   = phase_ * TWO_PI_RECIP;
            out = phase_ < (float)M_PI ? 1.0f : -1.0f;
            out += Polyblep(phase_inc_, t);
            out -= Polyblep(phase_inc_, fmodf(t + 0.5f, 1.0f));
            out *= 0.707f; // ?
            break;
        default: out = 0.0f; break;
    }
    phase_ += phase_inc_;
    if(phase_ > TWO_PI_F)
    {
        phase_ -= TWO_PI_F;
    }
    return out * amp_;
}

float Oscillator::CalcPhaseInc(float f)
{
    return (TWO_PI_F * f) * sr_recip_;
}

static float Polyblep(float phase_inc, float t)
{
    float dt = phase_inc * TWO_PI_RECIP;
    if(t < dt)
    {
        t /= dt;
        return t + t - t * t - 1.0f;
    }
    else if(t > 1.0f - dt)
    {
        t = (t - 1.0f) / dt;
        return t * t + t + t + 1.0f;
    }
    else
    {
        return 0.0f;
    }
}
