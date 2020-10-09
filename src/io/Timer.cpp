#include "Timer.h"

#include <Arduino.h>

Timer::Timer() {
}

void Timer::start(unsigned long waitTime) {
    _running = true;
    _interrupted = true;
    _waitTime = waitTime;
    _startTime = micros();
}

void Timer::start() {
    _running = true;
    _interrupted = true;
    _startTime = micros();
}


void Timer::stop() {
    _running = false;
    _interrupted = true;
}

bool Timer::isRunning() {
    update();
    return _running;
}

bool Timer::isFinished() {
    update();
    return !_running && !_interrupted;
}

void Timer::update() {
    if(_running) {
        unsigned long timeDiff = micros() - _startTime;
        if(timeDiff > _waitTime) {
            _running = false;
            _interrupted = false;
        }
    }
}
