#ifndef Envelope_h
#define Envelope_h


class Point {
    public:
        Point() { x=0; y=0; }
        Point(float x, float y) { this->x = x; this->y = y; }
        float x;
        float y;
};

class Envelope
{
    public:
        static const int MAX_POINTS = 5;
        Envelope() {}
        void init(float sampleRate, int pointCount = 3, float length = 1, bool repeat = false);
        void reset();
        float process();

        void setIncrement(float increment) { this->increment = increment; }
        void setPoint(int index, Point point);
        void setSegmentLength(int index, float segmentLength);
        
    private:
        Point points[MAX_POINTS];
        int pointCount;
 
        float sampleRate;
        float increment;
        float position;
        bool repeat;
        bool end;

        int segment;
        float length;

        int getSegmentForPosition(float position);
        void incrementPosition();
};

#endif