#ifndef Formants_h
#define Formants_h

#include <inttypes.h>
#include "../../../modules/Formant.h"

#define VOCAL_FORMANT_SIZE 5

//Vocal formant values taken from C Sound manual http://www.csounds.com/manual/html/MiscFormants.html

#define SOPRANO_I      { Formant(270, 60, 1), Formant(2140, 90,  0.251189), Formant(2950, 100, 0.050119), Formant(3900, 120, 0.050119), Formant(4950, 120, 0.00631)  }
#define SOPRANO_E      { Formant(350, 60, 1), Formant(2000, 100, 0.1),      Formant(2800, 120, 0.177828), Formant(3600, 150, 0.01),     Formant(4950, 200, 0.001585) }
#define SOPRANO_A      { Formant(800, 80, 1), Formant(1150, 90,  0.501187), Formant(2900, 120, 0.025119), Formant(3900, 130, 0.1),      Formant(4950, 140, 0.003162) }
#define SOPRANO_O      { Formant(450, 40, 1), Formant(800,  80,  0.281838), Formant(2830, 100, 0.079433), Formant(3800, 120, 0.079433), Formant(4950, 120, 0.003162) }
#define SOPRANO_U      { Formant(325, 50, 1), Formant(700,  60,  0.158489), Formant(2700, 170, 0.017783), Formant(3800, 180, 0.01),     Formant(4950, 200, 0.001)    }

#define ALTO_I         { Formant(350, 50, 1), Formant(1700, 100, 0.1),      Formant(2700, 120, 0.031623), Formant(3700, 150, 0.015849), Formant(4950, 200, 0.001)    }
#define ALTO_E         { Formant(400, 60, 1), Formant(1600, 80,  0.063096), Formant(2700, 120, 0.031623), Formant(3300, 150, 0.017783), Formant(4950, 200, 0.001)    }
#define ALTO_A         { Formant(800, 80, 1), Formant(1150, 90,  0.630957), Formant(2800, 120, 0.1),      Formant(3500, 130, 0.015849), Formant(4950, 140, 0.001)    }
#define ALTO_O         { Formant(450, 70, 1), Formant(800,  80,  0.354813), Formant(2830, 100, 0.158489), Formant(3500, 130, 0.039811), Formant(4950, 135, 0.001778) }
#define ALTO_U         { Formant(325, 50, 1), Formant(700,  60,  0.251189), Formant(2530, 170, 0.031623), Formant(3500, 180, 0.01),     Formant(4950, 200, 0.000631) }

#define COUNTERTENOR_I { Formant(270, 40, 1), Formant(1850, 90,  0.063096), Formant(2900, 100, 0.063096), Formant(3350, 120, 0.015849), Formant(3590, 120, 0.015849) }
#define COUNTERTENOR_E { Formant(440, 70, 1), Formant(1800, 80,  0.199526), Formant(2700, 100, 0.125893), Formant(3000, 120, 0.1),      Formant(3300, 120, 0.1)      }
#define COUNTERTENOR_A { Formant(660, 80, 1), Formant(1120, 90,  0.501187), Formant(2750, 120, 0.070795), Formant(3000, 130, 0.063096), Formant(3350, 140, 0.012589) }
#define COUNTERTENOR_O { Formant(430, 40, 1), Formant(820,  80,  0.316228), Formant(2700, 100, 0.050119), Formant(3000, 120, 0.079433), Formant(3300, 120, 0.019953) }
#define COUNTERTENOR_U { Formant(370, 40, 1), Formant(630,  60,  0.1),      Formant(2750, 100, 0.070795), Formant(3000, 120, 0.031623), Formant(3400, 120, 0.019953) }

#define TENOR_I        { Formant(290, 40, 1), Formant(1870, 90,  0.177828), Formant(2800, 100, 0.125893), Formant(3250, 120, 0.1),      Formant(3540, 120, 0.031623) }
#define TENOR_E        { Formant(400, 70, 1), Formant(1700, 80,  0.199526), Formant(2600, 100, 0.251189), Formant(3200, 120, 0.199526), Formant(3580, 120, 0.1)      }
#define TENOR_A        { Formant(650, 80, 1), Formant(1080, 90,  0.501187), Formant(2650, 120, 0.446684), Formant(2900, 130, 0.398107), Formant(3250, 14,  0.079433) }
#define TENOR_O        { Formant(400, 70, 1), Formant(800,  80,  0.316228), Formant(2600, 100, 0.251189), Formant(2800, 130, 0.251189), Formant(3000, 135, 0.050119) }
#define TENOR_U        { Formant(350, 40, 1), Formant(600,  60,  0.1),      Formant(2700, 100, 0.141254), Formant(2900, 120, 0.199526), Formant(3300, 120, 0.050119) }

#define BASS_I         { Formant(250, 60, 1), Formant(1750, 90,  0.031623), Formant(2600, 100, 0.158489), Formant(3050, 120, 0.079433), Formant(3340, 120, 0.039811) }
#define BASS_E         { Formant(400, 40, 1), Formant(1620, 80,  0.251189), Formant(2400, 100, 0.354813), Formant(2800, 120, 0.251189), Formant(3100, 120, 0.125893) }
#define BASS_A         { Formant(600, 60, 1), Formant(1040, 70,  0.446684), Formant(2250, 110, 0.354813), Formant(2450, 120, 0.354813), Formant(2750, 130, 0.1)      }
#define BASS_O         { Formant(400, 40, 1), Formant(750,  80,  0.281838), Formant(2400, 100, 0.089125), Formant(2600, 120, 0.1),      Formant(2900, 120, 0.01)     }
#define BASS_U         { Formant(350, 40, 1), Formant(600,  80,  0.1),      Formant(2400, 100, 0.025119), Formant(2675, 120, 0.039811), Formant(2950, 120, 0.015849) }

#endif