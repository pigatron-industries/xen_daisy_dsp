#include <DaisyDuino.h>
#include "MainController.h"
#include "util/Profiler.h"
#include "io/Config.h"

#include "utility/gpio.h"

MainController* MainController::mainController = nullptr;

DaisyHardware hardware;

MainController::MainController() : AbstractMainController(Hardware::hw.rotaryEncoderButton) {
    mainController = this;
}

void MainController::audioCallback(float **in, float **out, size_t size) {
    MainController::mainController->process(in, out, size);
}

void MainController::init() {
    hardware = DAISY.init(DAISY_SEED, AUDIO_SR_48K);
    sampleRate = DAISY.get_samplerate();

    Hardware::hw.init();
    refreshTimer.start(100000);

    //AbstractMainController::init();
    controllerInit();
    
    Hardware::hw.display.setDisplayedPage(controllers.getSelected()->getDisplayPage());
    DAISY.begin(MainController::audioCallback);
}

void MainController::update() {
    RotaryEncoderButton::EncoderEvent event = encoder.getEncoderEvent();

    switch(event) {
        case RotaryEncoderButton::EncoderEvent::EVENT_HELD_CLOCKWISE:
            cycleController(1);
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_HELD_ANTICLOCKWISE:
            cycleController(-1);
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_CLOCKWISE: 
            controllers.getSelected()->event(event, controllers.getSelected()->getDisplayPage()->selectedItem);
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_ANTICLOCKWISE:
            controllers.getSelected()->event(event, controllers.getSelected()->getDisplayPage()->selectedItem);
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_SHORT_PRESS:
            controllers.getSelected()->getDisplayPage()->nextSelection();
            break;
        case RotaryEncoderButton::EncoderEvent::EVENT_LONG_HOLD:
            rebootToBootloader();
            break;
    }

    controllers.getSelected()->update();

    if(refreshTimer.isStopped()) {
        controllers.getSelected()->updateDisplay();
        refreshTimer.start(100000);
    }

    Hardware::hw.display.render();
}

void MainController::cycleController(int8_t direction) {
    Serial.println("controllerChange");
    DAISY.end();

    controllers.cycle(direction);
    controllerInit();

    DAISY.begin(MainController::audioCallback);
    DAISY.end();
    DAISY.begin(MainController::audioCallback);
}

void MainController::controllerInit() {
    //AbstractMainController::controllerInit();
    configMode.data.controllerIndex = controllers.getSelectedIndex();
    controllers.getSelected()->init();
 
    Hardware::hw.tempPool.reset();
    controllers.getSelected()->init(sampleRate);
    controllers.getSelected()->getDisplayPage()->setSelection(0);
    Hardware::hw.display.setDisplayedPage(controllers.getSelected()->getDisplayPage());
}

void MainController::process(float **in, float **out, size_t size) {
    PROFILE_START
    controllers.getSelected()->process(in, out, size);
    PROFILE_END
}

void MainController::rebootToBootloader() {
    Hardware::hw.display.alert("PROG");

    // Initialize Boot Pin
    dsy_gpio_pin bootpin = {DSY_GPIOG, 3};
    dsy_gpio pin;
    pin.mode = DSY_GPIO_MODE_OUTPUT_PP;
    pin.pin = bootpin;
    dsy_gpio_init(&pin);

    // Pull Pin HIGH
    dsy_gpio_write(&pin, 1);

	// wait a few ms for cap to charge
	delay(10);

    // Software Reset
	HAL_NVIC_SystemReset();
}