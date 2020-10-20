#ifndef StereoPan_h
#define StereoPan_h


/** Synthesis of several waveforms, including polyBLEP bandlimited waveforms.
*/
class StereoPan
{
  public:
    StereoPan() {}
    void process(float in);
    float getLeftOut() { return left; }
    float getRightOut() { return right; }

    void setPan(float pan);

  private:
    float leftGain = 0.5;
    float rightGain = 0.5;
    float left;
    float right;
};


inline void StereoPan::process(float in) {
    left = in * leftGain;
    right = in * rightGain;
}

inline void StereoPan::setPan(float pan) {
    leftGain = pan;
    rightGain = 1-pan;
}


#endif