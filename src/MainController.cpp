#include "MainController.h"
#include "util/Profiler.h"

void MainController::registerController(Controller* controller) {
    controllers[controllerSize] = controller;
    controllerSize++;
}

void MainController::init(float sampleRate) {
    Hardware::hw.init();
    refreshTimer.start(100000);
    for(int i = 0; i < controllerSize; i++) {
        controllers[i]->init(sampleRate);
    }
    Hardware::hw.display.setDisplayedPage(controllers[activeController]->getDisplayPage());
}

void MainController::update() {
    UIEvent event = updateUIEvent();

    if(controllers[activeController]->getDisplayPage()->selectedItem == 0) {
        // When title is selected then encoder switches controller
        if(event == UIEvent::EVENT_CLOCKWISE) {
            activeController = ((activeController + 1) % (controllerSize));
            controllers[activeController]->getDisplayPage()->setSelection(0);
            Hardware::hw.display.setDisplayedPage(controllers[activeController]->getDisplayPage());
        } else if(event == UIEvent::EVENT_COUNTERCLOCKWISE) {
            activeController = activeController > 0 ? activeController - 1 : controllerSize - 1;
            controllers[activeController]->getDisplayPage()->setSelection(0);
            Hardware::hw.display.setDisplayedPage(controllers[activeController]->getDisplayPage());
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
    
    PROFILE_DUMP
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
    //PROFILE_START
    controllers[activeController]->process(in, out, size);
    //PROFILE_END
}
