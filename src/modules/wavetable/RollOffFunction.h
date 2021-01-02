#ifndef RollOffFunction_h
#define RollOffFunction_h

class RollOffFunction {
    public:
        virtual float rolloff(int harmonic) = 0;
};

class SquareRollOffFunction : public RollOffFunction {
    public:
        virtual float rolloff(int harmonic) {
            return harmonic % 2 == 0 ? 0 : 
                                       1.0 / float(harmonic);
        }
};

class TriangleRollOffFunction : public RollOffFunction {
    public:
        virtual float rolloff(int harmonic) {
            return harmonic % 2 == 0 ? 0 : 
                   harmonic % 4 == 1 ? 1.0 / float(harmonic*harmonic) :
                                       -1.0 / float(harmonic*harmonic);
        }
};

class RampRollOffFunction : public RollOffFunction {
    public:
        virtual float rolloff(int harmonic) {
            return 1.0 / float(harmonic);
        }
};

#endif