#ifndef Spatializer_h
#define Spatializer_h

#include "../../../modules/delays/MultitapDelay.h"

class Position {
    public:
        Position() {}
        Position(float x, float y, float z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }
        float x;
        float y;
        float z;
};

class Spatializer {
    public:
        Spatializer();
        void init(float sampleRate, float maxDelay = 0.2);
        void process(float in);

        float getOutput(int index);

        void setSourcePosition(float x, float y, float z=0);
        void setDestinationPosition(int index, float x, float y, float z=0);

    private:
        MultitapDelay delay;
        float sampleRate;

        Position sourcePosition;
        Position destinationPosition[2];
        int destinationCount = 2;

        float inverseSpeed = 1.0/343.2;
        float near = 0.1;
        float far = 10;
	    float rollOff;

        void calcDelay(int index);
        void calcRollOff();
};

#endif
