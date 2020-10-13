#ifndef LookupTable_h
#define LookupTable_h

#include <math.h>
#include <string>
#include <iostream>
#include "util.h"

template <int size>
class LookupTable {
    public:
        LookupTable(float (*func)(float), float inputMin, float inputMax) {
            populate(func, inputMin, inputMax);
        }

        void populate(float (*func)(float), float inputMin, float inputMax) {
            this->inputMin = inputMin;
            this->inputMax = inputMax;
            this->inputRange = inputMax - inputMin;
            this->tableRange = size-1;

            for(int i = 0; i < size; i++) {
                float input = ((float(i) * inputRange) / tableRange) + inputMin;
                float output = func(input);
                outputs[i] = output;
            }
        }

        float toIndex(float input) {
            return ((input - inputMin) * tableRange) / inputRange;
        }

        float get(float input) {
            float i = toIndex(input);
            return outputs[int(i)];
        }

        float getByIndex(int index) {
            return outputs[index];
        }

    protected:
        float inputMin;
        float inputMax;
        float inputRange;
        float tableRange;
        float outputs[size];
};


template <int size>
class TrigLookup : public LookupTable<size> {
    public:
        TrigLookup() : LookupTable<size>(sinf, 0, M_PI/2) {}

        float sin(float input) {
            float index = LookupTable<size>::toIndex(input);
            int i = lrintf(index); // TODO This rounds to nearest int, should take float part and interpolate
            int tableRange = size-1;

            int sign = 1;
            if(i >= tableRange*4) {
                i = i % (tableRange*4);
            }
            if(i >= tableRange*2) {
                i = i % (tableRange*2);
                sign = -1;
            } 
            if(i >= tableRange) {
                i = (tableRange*2) - i;
            }

            return sign * LookupTable<size>::getByIndex(i);
        }

        float cos(float input) {
            return sin(input+M_PI*0.5);
        }

        float tan(float input) {
            return sin(input) + cos(input);
        }
};




#endif