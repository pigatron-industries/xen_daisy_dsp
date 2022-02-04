#include <DaisyDuino.h>
#include <Arduino.h>
#include "MainController.h"
#include "io/Hardware.h"
#include "apps.h"

MainController mainController = MainController();

void setup() {
    Serial.begin(115200);
    Serial.println("Pigatron Industries");

    mainController.init();
}

void loop() {
    mainController.update();
}
