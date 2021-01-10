#include "TractController.h"

#define LEFT 0
#define RIGHT 1


void TractController::init(float sampleRate) {
    tract.init(sampleRate, 48, defaultTractProps(15));

    displayPage.initTitle("Vocal Tract", "TRCT");
}

void TractController::update() {
    tongueX.update();
    tongueY.update();
    constrictionX.update();
    constrictionY.update();
}

void TractController::process(float **in, float **out, size_t size) {
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
        out[RIGHT][i] = vocalOutput;
    }

    //Update Parameters
    float tongueIndex = tongueX.getValue() * ((float) (tract.tongueIndexUpperBound() - tract.tongueIndexLowerBound())) + tract.tongueIndexLowerBound();
	float innerTongueControlRadius = 2.05;
	float outerTongueControlRadius = 3.5;
    float tongueDiameter = tongueY.getValue() * (outerTongueControlRadius - innerTongueControlRadius) + innerTongueControlRadius;
    float constrictionMin = 0.31;
    float constrictionMax = 2.0;
    float constrictionIndex = constrictionX.getValue() * (float) tract.getTractIndexCount();
    float constrictionDiameter = constrictionY.getValue();
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
