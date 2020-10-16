#ifndef Profiler_h
#define Profiler_h

#include <Arduino.h>

#ifdef PROFILE_PROCESS
    #define PROFILE_START Profiler::profiler.start();                                                                     
    #define PROFILE_END Profiler::profiler.end();  
    #define PROFILE_DUMP if(Profiler::profiler.isFull()) { Profiler::profiler.dumpAverageTime(); }
#else
    #define PROFILE_START                                                                   
    #define PROFILE_END
    #define PROFILE_DUMP
#endif

#define PROFILER_SAMPLES 1000

class Profiler {
    public:
        static Profiler profiler;

        Profiler() {}

        inline void start() {
            startTime = micros();
        }

        inline void end() {
            if(!full) {
                unsigned long endTime = micros();
                if(endTime > startTime) {
                    times[position++] = endTime - startTime;
                    if(position >= PROFILER_SAMPLES) {
                        position = 0;
                        full = true;
                    }
                }
            }
        }

        inline bool isFull() {
            return full;
        }

        inline void dumpAverageTime() {
            unsigned long average = 0;
            for(int i = 0; i < PROFILER_SAMPLES; i++) {
                average += times[i];
            }
            average = average / PROFILER_SAMPLES;
            Serial.print("Average time: ");
            Serial.println(average);
            full = false;
            position = 0;
        }


    private:
        unsigned long startTime;
        unsigned long times[PROFILER_SAMPLES];
        bool full;
        int position = 0;

};

#endif