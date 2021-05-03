#ifndef ArrayInterpolation_h
#define ArrayInterpolation_h

/**
 * Represents a bank of related frequencies
 */
class ArrayInterpolation {
    public:
        void setInterpolation(float interpolation) {
            this->interpolation = interpolation;
            interpolationIndex = static_cast<int>(interpolation);
            interpolationFraction = interpolation - static_cast<float>(interpolationIndex);
        }

        float interpolate(float a, float b) {
            return a + (b - a) * interpolationFraction;
        }

        float interpolation = 0;
        int interpolationIndex = 0;
        float interpolationFraction = 0;
};

#endif
