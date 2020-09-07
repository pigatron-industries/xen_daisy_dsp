#ifndef Tract_h
#define Tract_h

#include <inttypes.h>

#define MAX_TRANSIENTS 20
#define MAX_TRACT_SIZE 50

typedef struct t_transient {
	int position;
	float timeAlive;
	float lifeTime;
	float strength;
	float exponent;
	bool living;
} t_transient;

typedef struct t_tractProps {
	int n;
	int lipStart;
	int bladeStart;
	int tipStart;
	int noseStart;
	int noseLength;
	float noseOffset;
	float tongueIndex;
	float tongueDiameter;
	float noseDiameter[MAX_TRACT_SIZE] = {0};
	float tractDiameter[MAX_TRACT_SIZE] = {0};
} t_tractProps;

t_tractProps defaultTractProps(int n);

 
class Tract {
    public:
        Tract();
        void init(float sampleRate, float blockTime, t_tractProps props);
        void process(float glottalOutput, float turbulenceNoise, float lambda);
        void finishBlock();

        void setRestDiameter(float tongueIndex, float tongueDiameter);
	    void setConstriction(float cindex, float cdiam, float fricativeIntensity);

        float getLipOutput() { return lipOutput; }
        float getNoseOutput() { return noseOutput; }

        long getTractIndexCount() { return tractProps.n; }
        long tongueIndexLowerBound() { return tractProps.bladeStart+2; }
        long tongueIndexUpperBound() { return tractProps.tipStart-3; }

    private:
        t_tractProps tractProps;

        float sampleRate, blockTime;
        float glottalReflection;
        float lipReflection;
        int lastObstruction;
        float fade;
        float movementSpeed;
        float velumTarget;
        t_transient transients[MAX_TRANSIENTS];
        int transientCount;
        
        float diameter[MAX_TRACT_SIZE] = {0.0};
        float restDiameter[MAX_TRACT_SIZE] = {0.0};
        float targetDiameter[MAX_TRACT_SIZE] = {0.0};
        float newDiameter[MAX_TRACT_SIZE] = {0.0};
        
        float R[MAX_TRACT_SIZE] = {0.0};
        float L[MAX_TRACT_SIZE] = {0.0};
        float reflection[MAX_TRACT_SIZE+1] = {0.0};
        float newReflection[MAX_TRACT_SIZE+1] = {0.0};
        float junctionOutputR[MAX_TRACT_SIZE+1] = {0.0};
        float junctionOutputL[MAX_TRACT_SIZE+1] = {0.0};
        float A[MAX_TRACT_SIZE] = {0.0};
        float maxAmplitude[MAX_TRACT_SIZE] = {0.0};
        
        float noseR[MAX_TRACT_SIZE] = {0.0};
        float noseL[MAX_TRACT_SIZE] = {0.0};
        float noseJunctionOutputR[MAX_TRACT_SIZE+1] = {0.0};
        float noseJunctionOutputL[MAX_TRACT_SIZE+1] = {0.0};
        float noseReflection[MAX_TRACT_SIZE+1] = {0.0};
        float noseDiameter[MAX_TRACT_SIZE] = {0.0};
        float noseA[MAX_TRACT_SIZE] = {0.0};
        float noseMaxAmplitude[MAX_TRACT_SIZE] = {0.0};
        
        float reflectionLeft, reflectionRight, reflectionNose;
        float newReflectionLeft, newReflectionRight, newReflectionNose;
        
        float constrictionIndex;
        float constrictionDiameter;
        float fricativeIntensity = 0.0;

        float lipOutput;
	    float noseOutput;

        void init();
        void addTransient(int position);
        void addTurbulenceNoise(float turbulenceNoise);
        void addTurbulenceNoiseAtIndex(float turbulenceNoise, float index, float diameter);
        float getNoiseModulator();
        void calculateReflections();
        void calculateNoseReflections();
        void processTransients();
        void reshapeTract(float deltaTime);
};

#endif