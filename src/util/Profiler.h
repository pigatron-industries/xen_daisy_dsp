#ifndef Profiler_h
#define Profiler_h

#include <Arduino.h>

#define PROFILER_SAMPLES 1000

class Profiler {
    public:
        Profiler() {}

        inline void start() {
            startTime = micros();
        }

        inline void stop() {
            times[position] = micros() - startTime;
            if(position >= PROFILER_SAMPLES) {
                position = 0;
                dumpAverageTime();
            }
        }

        inline void dumpAverageTime() {
            unsigned long average = 0;
            for(int i = 0; i < PROFILER_SAMPLES; i++) {
                average += times[i];
            }
            average = average / PROFILER_SAMPLES;
            Serial.print("Average time: ");
            Serial.println(average);
        }


    private:
        unsigned long startTime;
        unsigned long times[PROFILER_SAMPLES];
        int position = 0;

};

#endif