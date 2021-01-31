#include "PowerFunction.h"
#include "../../util/util.h"

float PowerFunction::process(float in) {
    return powf(in, power);
}
