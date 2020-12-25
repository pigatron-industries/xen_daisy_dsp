#include "GlitchLoopController.h"



void GlitchLoopController::init(float sampleRate) {
    this->sampleRate = sampleRate;
    buffer1.init(sampleRate * MAX_DELAY);
    buffer2.init(sampleRate * MAX_DELAY);
    state = GlitchState::GLITCH_OFF;
    displayPage.initTitle("Glitch Loop");
}

void GlitchLoopController::update() {

    float delayTimeLeft = 0.0;
    float delayTimeRight = 0.0;

    if(sampleTimeInput.update()) {
        buffer1.setSampleSize(sampleRate * sampleTimeInput.getValue());
        buffer2.setSampleSize(sampleRate * sampleTimeInput.getValue());
    }

    if(writeDelayStartInput.update()) {
        writeDelaySamples = writeDelayStartInput.getValue() * sampleRate;
    }

    if(readDelayStartInput.update()) {
        readDelaySamples = readDelayStartInput.getValue() * sampleRate;
    }

    if(dryGainInput.update()) {
        dryGain = dryGainInput.getValue();
    }

    if(gateInput.update()) {
        if(!gateInput.isOpen()) {
            state = GlitchState::GLITCH_OFF;
        }
        if(gateInput.isTriggered()) {
            state = writeDelaySamples > 0 ? GlitchState::GLITCH_WRITE_DELAY : GlitchState::GLITCH_WRITE;
            writeDelayCounter = 0;
            buffer1.reset();
            buffer2.reset();
        }
    }
}

void GlitchLoopController::process(float **in, float **out, size_t size) {
    bool full;
    for (size_t i = 0; i < size; i++) {

        switch (state) {
            case GlitchState::GLITCH_WRITE_DELAY:
                writeDelayCounter++;
                if(writeDelayCounter >= writeDelaySamples) {
                    state = GlitchState::GLITCH_WRITE;
                }
                out[0][i] = in[0][i];
                out[1][i] = in[1][i];
                break;

            case GlitchState::GLITCH_WRITE:
                buffer1.write(in[0][i]);
                buffer2.write(in[1][i]);
                if(buffer1.isSampleFull()) {
                    state = readDelaySamples > 0 ? GlitchState::GLITCH_READ_DELAY : GlitchState::GLITCH_READ;
                    readDelayCounter = 0;
                }
                out[0][i] = in[0][i];
                out[1][i] = in[1][i];
                break;

            case GlitchState::GLITCH_READ_DELAY:
                if(!buffer1.isBufferFull()) {
                    buffer1.write(in[0][i]);
                    buffer2.write(in[1][i]);
                }
                readDelayCounter++;
                if(readDelayCounter >= readDelaySamples) {
                    state = GlitchState::GLITCH_READ;
                }
                out[0][i] = in[0][i];
                out[1][i] = in[1][i];
                break;

            case GlitchState::GLITCH_READ:
                if(!buffer1.isBufferFull()) {
                    buffer1.write(in[0][i]);
                    buffer2.write(in[1][i]);
                }
                out[0][i] = buffer1.read() + in[0][i]*dryGain;
                out[1][i] = buffer2.read() + in[1][i]*dryGain;
                buffer1.readIncrement();
                buffer2.readIncrement();
                break;

            case GlitchState::GLITCH_OFF:
                out[0][i] = in[0][i];
                out[1][i] = in[1][i];
        }
    }
}