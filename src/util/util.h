#ifndef util_h
#define util_h

//#include <math.h>
#include <Arduino.h>

#define M_PI 3.14159265358979323846f


static inline float maxf(float a, float b) {
	if (a > b) return a;
	return b;
}

static inline float minf(float a, float b) {
	if (a < b) return a;
	return b;
}

static inline float clamp(float number, float min, float max) {
	if (number < min) return min;
	else if (number > max) return max;
	else return number;
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