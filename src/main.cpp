#include <DaisyDuino.h>
#include <Arduino.h>
#include "MainController.h"
#include "io/Hardware.h"
#include "apps.h"

void setup() {
    Serial.begin(115200);
    Serial.println("Pigatron Industries");

    registerApps();

    // Initialize for Daisy pod at 48kHz
    MainController::instance.init();
}

void loop() {
    MainController::instance.update();
}
