#include <DaisyDuino.h>
#include "MainController.h"
#include "util/Profiler.h"
#include "io/MemPool.h"
#include "io/Config.h"

// Temp workaround for linker issue in DaisyDuino lib
#include "utility/hid_audio.h"
extern "C" {
    void audio_stop(uint8_t intext);
}

MainController MainController::instance;

void MainController::audioCallback(float **in, float **out, size_t size) {
    MainController::instance.process(in, out, size);
}


void MainController::registerController(Controller* controller) {
    controllers[controllerSize] = controller;
    controllerSize++;
    controller->getDisplayPage()->setNumber(0, controllerSize);
}

void MainController::init(float sampleRate) {
    this->sampleRate = sampleRate;
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
    Serial.println("MainController::update START");

    UIEvent event = updateUIEvent();

    if(controllers[activeController]->getDisplayPage()->selectedItem == 0) {
        // When title is selected then encoder switches controller
        if(event == UIEvent::EVENT_CLOCKWISE) {
            int controllerIndex = ((activeController + 1) % (controllerSize));
            setActiveController(controllerIndex);
        } else if(event == UIEvent::EVENT_COUNTERCLOCKWISE) {
            int controllerIndex = activeController > 0 ? activeController - 1 : controllerSize - 1;
            setActiveController(controllerIndex);
        }
        if(event == UIEvent::EVENT_SHORT_PRESS) {
            controllers[activeController]->getDisplayPage()->setSelection(-1);
        }
    } else {
        if(event == UIEvent::EVENT_CLOCKWISE) {
            controllers[activeController]->event(event, controllers[activeController]->getDisplayPage()->selectedItem);
        } else if (event == UIEvent::EVENT_COUNTERCLOCKWISE) {
            controllers[activeController]->event(event, controllers[activeController]->getDisplayPage()->selectedItem);
        }
        if(event == UIEvent::EVENT_SHORT_PRESS) {
            controllers[activeController]->getDisplayPage()->nextSelection();
        }
        if(event == UIEvent::EVENT_LONG_PRESS) {
            controllers[activeController]->getDisplayPage()->setSelection(0);
        }
    }

    controllers[activeController]->update();

    if(refreshTimer.isFinished()) {
        controllers[activeController]->updateDisplay();
        refreshTimer.start();
    }

    Hardware::hw.display.render();
    
    Serial.println("MainController::update END");
    PROFILE_DUMP
}

void MainController::setActiveController(int controllerIndex) {
    Serial.println("MainController::setActiveController START");
    //DAISY.end();
    audio_stop(DSY_AUDIO_INTERNAL);  // Temp workaround for linker issue in DaisyDuino lib
 
    MemPool::resetPool();
    controllers[controllerIndex]->init(sampleRate);
    controllers[controllerIndex]->getDisplayPage()->setSelection(0);
    Hardware::hw.display.setDisplayedPage(controllers[controllerIndex]->getDisplayPage());
    Config::setSelectedApp(controllerIndex);
    activeController = controllerIndex;

    DAISY.begin(MainController::audioCallback);
    Serial.println("MainController::setActiveController END");
}

UIEvent MainController::updateUIEvent() {
    Hardware::hw.encoderButton.update();
    Hardware::hw.encoder.tick();
    RotaryEncoder::Direction dir = Hardware::hw.encoder.getDirection();

    if(Hardware::hw.encoderButton.held() && Hardware::hw.encoderButton.duration() >= 1000) {
        return UIEvent::EVENT_LONG_PRESS;
    }
    if(dir == RotaryEncoder::Direction::CLOCKWISE) {
        return UIEvent::EVENT_CLOCKWISE;
    }
    if(dir == RotaryEncoder::Direction::COUNTERCLOCKWISE) {
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
