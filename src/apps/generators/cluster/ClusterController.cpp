#include "ClusterController.h"

#define LEFT 0
#define RIGHT 1

void ClusterController::init(float sampleRate) {
    displayPage.initTitle("Cluster", "CLST");
}

void ClusterController::process(float **in, float **out, size_t size) {
    for (size_t i = 0; i < size; i++) {
        out[LEFT][i] = out[LEFT][i];
        out[RIGHT][i] = out[LEFT][i];
    }
}

void ClusterController::update() {

}
