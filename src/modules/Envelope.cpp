#include "Envelope.h"

void Envelope::init(int pointCount, float length, bool repeat) {
    this->pointCount = pointCount;
    this->length = length;
    this->repeat = repeat;

    // start with evenly distributed points
    float segmentLength = length / float(pointCount);
    for(int i = 0; i < pointCount; i++) {
        points[i] = Point(segmentLength * float(i), 0);
    }
}

void Envelope::reset() {
    end = false;
    position = 0;
}

float Envelope::process() {
    if(end) {
        return points[pointCount-1].y;
    }

    Point point1 = points[segment];
    Point point2 = points[segment+1];
    float gradient = (point2.y-point1.y) / (point2.x-point1.x); //TODO precalculate gradients
    float segmentX = position - point1.x;
    float segmentY = segmentX * gradient;
    float value = point1.y + segmentY;

    incrementPosition();
    return value;
}

void Envelope::incrementPosition() {
    position += increment;
    if(position > points[segment+1].x) {
        segment++;
    }
    if(repeat && position > length) {
        position -= length;
        segment = getSegmentForPosition(position);
    } else {
        end = true;
    }
}

void Envelope::setPoint(int index, Point point) {
    if(index > 0 && point.x < points[index-1].x) {
        point.x = points[index-1].x;
    } else if(index < pointCount-1 && point.x > points[index+1].x) {
        point.x = points[index+1].x;
    }
    points[index] = point;

    if(index == pointCount-1) {
        length = point.x;
    }

    //TODO recalculate gradient for segment before and after point
}

int Envelope::getSegmentForPosition(float position) {
    for(int i = 0; i < pointCount; i++) {
        if(points[i].x > position) {
            return i-1;
        }
    }
    return pointCount-1;
}
