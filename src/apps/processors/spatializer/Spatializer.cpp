#include "Spatializer.h"

#include <math.h>

Spatializer::Spatializer() {
    calcRollOff();
}

void Spatializer::init(float sampleRate, float maxDelay) {
    this->sampleRate = sampleRate;
    delay.init(sampleRate, maxDelay);
    delay.setTapCount(destinationCount);
}

void Spatializer::process(float in) {
    delay.write(in);
}

float Spatializer::getOutput(int index) {
    return delay.readTap(index);
}

void Spatializer::setSourcePosition(float x, float y, float z) {
    sourcePosition = Position(x, y, z);
    for(int i = 0; i < destinationCount; i++) {
        calcDelay(i);
    }
}

void Spatializer::setDestinationPosition(int index, float x, float y, float z) {
    destinationPosition[index] = Position(x, y, z);
    calcDelay(index);
}

void Spatializer::calcDelay(int index) {
    float x = destinationPosition[index].x - sourcePosition.x;
    float y = destinationPosition[index].y - sourcePosition.y;
    float z = destinationPosition[index].z - sourcePosition.z;
    float dist = sqrt(x*x+y*y+z*z);
    float delayTime = dist * inverseSpeed;

    float gain = 1;
    if(dist > near) {
        gain = near / (near + rollOff * (dist - near));
    }
	
    delay.setTap(index, delayTime, gain);
}

void Spatializer::calcRollOff() {
    rollOff = (near/0.25 - near) / (far - near);
}