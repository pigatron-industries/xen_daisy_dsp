#ifndef util_h
#define util_h

#include <Arduino.h>
#include <utility/DaisySP/modules/dsp.h>

using namespace daisysp;

#define M_PI 3.14159265358979323846f
#define ONE_OVER_ROOT_TWO 0.70710678


static inline float moveTowards(float current, float target, float amount) {
	if (current < target) return daisysp::fmin(current + amount, target);
	else return daisysp::fmax(current - amount, target);
}

static inline float moveTowards(float current, float target, float amountUp, float amountDown) {
	if (current < target) return daisysp::fmin(current + amountUp, target);
	else return daisysp::fmax(current - amountDown, target);
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

inline float smooth(float currentValue, float prevValue, float smoothing = 0.2) {
    return (currentValue*smoothing) + prevValue*(1-smoothing);
}

#endif