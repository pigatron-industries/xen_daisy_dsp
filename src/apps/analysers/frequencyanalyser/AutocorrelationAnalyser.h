#ifndef AutocorrelationAnalyser_h
#define AutocorrelationAnalyser_h

#define AUTOCORRELATION_BUFFER_SIZE 1200  //minimum frequency = 40Hz

class AutocorrelationAnalyser {
    public:
        AutocorrelationAnalyser() {}
        void init(float sampleRate);
        void process(float in);
    
        bool calculate();
        bool bufferFull() { return bufferPosition == AUTOCORRELATION_BUFFER_SIZE; }
        float getFrequency() { return frequency; }

    private:
        float sampleRate;

        int bufferPosition = 0;
        float buffer[AUTOCORRELATION_BUFFER_SIZE];

        float frequency = 0;

        void compute();

};

#endif