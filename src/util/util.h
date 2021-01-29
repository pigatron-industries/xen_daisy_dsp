#ifndef util_h
#define util_h

//#include <math.h>
#include <Arduino.h>

#define M_PI 3.14159265358979323846f
#define ONE_OVER_ROOT_TWO 0.70710678


static inline float maxf(float a, float b) {
    float r;
	#ifdef __arm__
		asm("vmaxnm.f32 %[d], %[n], %[m]" : [d] "=t"(r) : [n] "t"(a), [m] "t"(b) :);
	#else
		r = (a > b) ? a : b;
	#endif
    return r;
}

static inline float minf(float a, float b) {
    float r;
	#ifdef __arm__
		asm("vminnm.f32 %[d], %[n], %[m]" : [d] "=t"(r) : [n] "t"(a), [m] "t"(b) :);
	#else
		r = (a < b) ? a : b;
	#endif
    return r;
}

static inline float clamp(float in, float min, float max) {
	return minf(maxf(in, min), max);
}

/** From Musicdsp.org "Fast power and root estimates for 32bit floats)
Original code by Stefan Stenzel
These are approximations
*/
inline float fastpower(float f, int n) {
    long *lp, l;
    lp = (long *)(&f);
    l  = *lp;
    l -= 0x3F800000;
    l <<= (n - 1);
    l += 0x3F800000;
    *lp = l;
    return f;
}

inline float fastroot(float f, int n) {
    long *lp, l;
    lp = (long *)(&f);
    l  = *lp;
    l -= 0x3F800000;
    l >>= (n = 1);
    l += 0x3F800000;
    *lp = l;
    return f;
}

/* Original code for fastlog2f by Dr. Paul Beckmann from the ARM community forum, adapted from the CMSIS-DSP library
About 25% performance increase over std::log10f
*/
inline float fastlog2f(float f) {
    float frac;
    int   exp;
    frac = frexpf(fabsf(f), &exp);
    f    = 1.23149591368684f;
    f *= frac;
    f += -4.11852516267426f;
    f *= frac;
    f += 6.02197014179219f;
    f *= frac;
    f += -3.13396450166353f;
    f += exp;
    return (f);
}

/** From http://openaudio.blogspot.com/2017/02/faster-log10-and-pow.html
No approximation, pow10f(x) gives a 90% speed increase over powf(10.f, x)
*/
inline float pow10f(float f) {
    return expf(2.302585092994046f * f);
}

inline float fastlog10f(float f) {
    return fastlog2f(f) * 0.3010299956639812f;
}

static inline float moveTowards(float current, float target, float amount) {
	if (current < target) return minf(current + amount, target);
	else return maxf(current - amount, target);
}

static inline float moveTowards(float current, float target, float amountUp, float amountDown) {
	if (current < target) return minf(current + amountUp, target);
	else return maxf(current - amountDown, target);
}

static inline float gaussian() {
	float s = 0;
	for (int c = 0; c < 16; c++) s += (float) rand() / (float) RAND_MAX;
	return (s - 8.0) / 4.0;
}

inline void zeroBuffer(float* buffer, int len) {
    for (int i = 0; i < len; i++)
        buffer[i] = 0.0;
}

inline void gain(float* buffer, float gain, int len) {
    for (int i = 0; i < len; i++) { 
        buffer[i] *= gain;
    }
}

static float db2gain(float input) {
    return std::pow(10, input / 20.0);
}

static float randf(float minf, float maxf) {
  return minf + random(1UL << 31) * (maxf - minf) / (1UL << 31);  // use 1ULL<<63 for max double values)
}

#endif