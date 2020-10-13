#ifndef LookupTable_h
#define LookupTable_h

#include <math.h>
#include <string>
#include <iostream>

template <int tableSize>
class LookupTable {
    public:
        LookupTable(float (*func)(float), float inputMin, float inputMax) {
            populate(func, inputMin, inputMax);
        }

        void populate(float (*func)(float), float inputMin, float inputMax) {
            this->inputMin = inputMin;
            this->inputMax = inputMax;
            this->inputRange = inputMax - inputMin;
            this->tableRange = tableSize-1;

            for(int i = 0; i < tableSize; i++) {
                float input = ((float(i) * inputRange) / tableRange) + inputMin;
                float output = func(input);
                outputs[i] = output;
            }
        }

        int toIndex(float input) {
            return int(((input - inputMin) * tableRange) / inputRange);
        }

        float get(float input) {
            float i = ((input - inputMin) * tableRange) / inputRange;
            return outputs[int(i)];
        }

        float getByIndex(int index) {
            return outputs[index];
        }

    private:
        float inputMin;
        float inputMax;
        float inputRange;
        float tableRange;
        float outputs[tableSize];
};


template <int tableSize>
class TrigLookup : public LookupTable<tableSize> {
    public:
        TrigLookup() : LookupTable<tableSize>(sinf, 0, M_PI/2) {}

        float sin(float input) {
            int sign = 1;
            if(input >= M_PI*2) {
                input = fmod(input, M_PI*2);
            }
            if(input >= M_PI) {
                input = fmod(input, M_PI);
                sign = -1;
            } else if(input >= M_PI*0.5001) {
                input = M_PI - input;
            }
            return sign * LookupTable<tableSize>::get(input);
        }
};




#endif