#ifndef LookupTable_h
#define LookupTable_h


template <int size>
class LookupTable {
    public:
        LookupTable(float (*func)(float), float inputMax) {
            populate(func, inputMax);
        }

        void populate(float (*func)(float), float inputMax) {
            this->inputMax = inputMax;
            this->tableRange = size-1;
            this->rangeFactor = tableRange / inputMax;

            for(int i = 0; i < size; i++) {
                float input = ((float(i) * inputMax) / tableRange);
                float output = func(input);
                outputs[i] = output;
            }
        }

        float toIndex(float input) {
            return input * rangeFactor;
        }

        float get(float input) {
            float i = toIndex(input);
            return outputs[int(i)];
        }

        float getByIndex(int index) {
            return outputs[index];
        }

    protected:
        float inputMax;
        float tableRange;
        float rangeFactor;
        float outputs[size];
};


template <int size>
class TrigLookup : public LookupTable<size> {
    public:
        TrigLookup() : LookupTable<size>(sinf, M_PI/2) {}

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

#define TRIG_LOOKUP_SIZE 50

class LookupTables {
    public:
        static TrigLookup<TRIG_LOOKUP_SIZE> trigLookup;
};

TrigLookup<TRIG_LOOKUP_SIZE> LookupTables::trigLookup;


#endif