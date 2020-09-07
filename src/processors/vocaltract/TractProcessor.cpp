#include "TractProcessor.h"

#define LEFT 0
#define RIGHT 1

TractProcessor::TractProcessor():
    tongueX(A0, -5, 5, 0, 1),
    tongueY(A1, -5, 5, 0, 1),
    constrictionX(A2, -5, 5, 0, 1),
    constrictionY(A3, -5, 5, 0.3, 2) {
}

void TractProcessor::init(float sampleRate) {
    tract.init(sampleRate, 48, defaultTractProps(15));
}

void TractProcessor::update() {
    tongueX.update();
    tongueY.update();
    constrictionX.update();
    constrictionY.update();
}

void TractProcessor::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        float lambda1 = (float)i / (float)size;
        float lambda2 = ((float)i + 0.5) / (float)size;

        //Noise
        float noise = whiteNoise.Process();
        float fricative = fricativeFilter.process(noise);

        //Tract
        float vocalOutput = 0.0;
        tract.process(in[LEFT][i], fricative, lambda1);
        vocalOutput += tract.getLipOutput() + tract.getNoseOutput();
        // tract.process(in[LEFT][i], fricative, lambda2);
        // vocalOutput += tract.getLipOutput() + tract.getNoseOutput();
        
        //Output
        out[LEFT][i] = vocalOutput;
    }

    //Update Parameters
    float tongueIndex = tongueX.getVirtualValue() * ((float) (tract.tongueIndexUpperBound() - tract.tongueIndexLowerBound())) + tract.tongueIndexLowerBound();
	float innerTongueControlRadius = 2.05;
	float outerTongueControlRadius = 3.5;
    float tongueDiameter = tongueY.getVirtualValue() * (outerTongueControlRadius - innerTongueControlRadius) + innerTongueControlRadius;
    float constrictionMin = 0.31;
    float constrictionMax = 2.0;
    float constrictionIndex = constrictionX.getVirtualValue() * (float) tract.getTractIndexCount();
    float constrictionDiameter = constrictionY.getVirtualValue();
    // if (constrictionActive) {
	// 	fricativeIntensity += 0.1; // TODO ex recto
	// 	fricativeIntensity = minf(1.0, fricativeIntensity);
	// } else {
    //     constrictionDiameter = constrictionMax;
	// } 

    if(constrictionDiameter <= 0.3) {
        constrictionDiameter = 0.31;
    }

    tract.setRestDiameter(tongueIndex, tongueDiameter);
	tract.setConstriction(constrictionIndex, constrictionDiameter, fricativeIntensity);
    tract.finishBlock();
}
