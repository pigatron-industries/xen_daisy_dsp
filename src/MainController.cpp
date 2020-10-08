#include "MainController.h"

MainController::MainController(Hardware& hardware, Controller** controllers, int size) : hw(hardware) {
    this->controllers = controllers;
    this->controllerSize = size;
}

void MainController::init(float sampleRate) {
    hw.init();
    for(int i = 0; i < controllerSize; i++) {
        controllers[i]->init(sampleRate);
    }
    render();
}

void MainController::update() {
    hw.encoder.tick();
    hw.encoderButton.update();

    if(!controllerSelectMode) {
        if(hw.encoderButton.held() && hw.encoderButton.duration() > 1000) {
            controllerSelectMode = true;
            render();
        }
        controllers[activeController]->update();
    } else {
        RotaryEncoder::Direction dir = hw.encoder.getDirection();
        if(dir == RotaryEncoder::Direction::CLOCKWISE) {
            activeController = ((activeController + 1) % (controllerSize));
            render();
        } else if(dir == RotaryEncoder::Direction::COUNTERCLOCKWISE) {
            activeController = activeController > 0 ? activeController - 1 : controllerSize - 1;
            render();
        }
        if(hw.encoderButton.pressed()) {
            controllerSelectMode = false;
            #if defined(XEN_TFT)
                hw.tft.fillScreen(TFT_BLACK);
            #endif
            render();
        }
    }
}

void MainController::process(float **in, float **out, size_t size) {
    controllers[activeController]->process(in, out, size);
}

void MainController::render() {
    #if defined(XEN_TFT)
        hw.tft.setCursor(2, 0, 2);
        if(controllerSelectMode) {
            hw.tft.fillRect(0, 0, hw.tft.width()-1, 16, TFT_NAVY);
            hw.tft.setTextColor(TFT_YELLOW, TFT_NAVY);
        } else {
            hw.tft.setTextColor(TFT_OLIVE, TFT_BLACK);
        }
        hw.tft.print(controllers[activeController]->getName());
        hw.tft.print("          ");
        hw.tft.drawLine(0, 16, hw.tft.width()-1, 16, TFT_OLIVE);

        if(!controllerSelectMode) {
            controllers[activeController]->render();
        }
    #endif
}
