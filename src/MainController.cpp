#include <DaisyDuino.h>
#include "MainController.h"
#include "util/Profiler.h"
#include "io/Config.h"

#include "utility/gpio.h"

MainController MainController::instance;

DaisyHardware hardware;

void MainController::audioCallback(float **in, float **out, size_t size) {
    MainController::instance.process(in, out, size);
}


void MainController::registerController(Controller* controller) {
    controllers[controllerSize] = controller;
    controllerSize++;
    controller->getDisplayPage()->setNumber(0, controllerSize);
}

void MainController::init() {
    hardware = DAISY.init(DAISY_SEED, AUDIO_SR_48K);
    sampleRate = DAISY.get_samplerate();

    Hardware::hw.init();
    refreshTimer.start(100000);

    activeController = Config::getSelectedApp();
    if(activeController >= controllerSize) {
        activeController = 0;
        Config::setSelectedApp(0);
    }

    controllers[activeController]->init(sampleRate);
    Hardware::hw.display.setDisplayedPage(controllers[activeController]->getDisplayPage());
    DAISY.begin(MainController::audioCallback);
}

void MainController::update() {
    UIEvent event = updateUIEvent();

    switch(event) {
        case UIEvent::EVENT_CLOCKWISE: 
            if(controllers[activeController]->getDisplayPage()->selectedItem == 0) {
                int controllerIndex = ((activeController + 1) % (controllerSize));
                setActiveController(controllerIndex);
            } else {
                controllers[activeController]->event(event, controllers[activeController]->getDisplayPage()->selectedItem);
            }
            break;
        case UIEvent::EVENT_COUNTERCLOCKWISE:
            if(controllers[activeController]->getDisplayPage()->selectedItem == 0) {
                int controllerIndex = activeController > 0 ? activeController - 1 : controllerSize - 1;
                setActiveController(controllerIndex);
            } else {
                controllers[activeController]->event(event, controllers[activeController]->getDisplayPage()->selectedItem);
            }
            break;
        case UIEvent::EVENT_SHORT_PRESS:
            controllers[activeController]->getDisplayPage()->nextSelection();
            break;
        case UIEvent::EVENT_LONG_PRESS:
            rebootToBootloader();
            break;
    }

    controllers[activeController]->update();

    if(refreshTimer.isStopped()) {
        controllers[activeController]->updateDisplay();
        refreshTimer.start(100000);
    }

    Hardware::hw.display.render();
}

void MainController::setActiveController(int controllerIndex) {
    DAISY.end();
 
    Hardware::hw.tempPool.reset();
    controllers[controllerIndex]->init(sampleRate);
    controllers[controllerIndex]->getDisplayPage()->setSelection(0);
    Hardware::hw.display.setDisplayedPage(controllers[controllerIndex]->getDisplayPage());
    Config::setSelectedApp(controllerIndex);
    activeController = controllerIndex;

    DAISY.begin(MainController::audioCallback);
    DAISY.end();
    DAISY.begin(MainController::audioCallback);
}

UIEvent MainController::updateUIEvent() {
    Hardware::hw.encoderButton.update();
    Hardware::hw.encoder.update();
    long movement = Hardware::hw.encoder.getMovement();

    if(Hardware::hw.encoderButton.held() && Hardware::hw.encoderButton.duration() >= 1000) {
        return UIEvent::EVENT_LONG_PRESS;
    }
    if(movement > 0) {
        return UIEvent::EVENT_CLOCKWISE;
    }
    if(movement < 0) {
        return UIEvent::EVENT_COUNTERCLOCKWISE;
    }
    if(Hardware::hw.encoderButton.released() && Hardware::hw.encoderButton.previousDuration() < 1000) {
        return UIEvent::EVENT_SHORT_PRESS;
    }
    return UIEvent::EVENT_NONE;
}

void MainController::process(float **in, float **out, size_t size) {
    PROFILE_START
    controllers[activeController]->process(in, out, size);
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