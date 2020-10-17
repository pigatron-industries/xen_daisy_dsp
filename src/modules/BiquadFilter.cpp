//
//  Biquad.cpp
//
//  Created by Nigel Redmon on 11/24/12
//  EarLevel Engineering: earlevel.com
//  Copyright 2012 Nigel Redmon
//
//  For a complete explanation of the Biquad code:
//  http://www.earlevel.com/main/2012/11/26/biquad-c-source-code/
//
//  License:
//
//  This source code is provided as is, without warranty.
//  You may copy and distribute verbatim copies of this document.
//  You may modify and use this source code to create binary code
//  for your own purposes, free or commercial.
//

#include <math.h>
#include "BiquadFilter.h"

BiquadFilter::BiquadFilter() {
    type = LOWPASS;
    a0 = 1.0;
    a1 = a2 = b1 = b2 = 0.0;
    fc = 0.50;
    q = 0.707;
    peakGain = 0.0;
    z1 = z2 = 0.0;
}

void BiquadFilter::init(float sampleRate) {
    this->sampleRate = sampleRate;
}

void BiquadFilter::setType(FilterType type) {
    this->type = type;
    calcBiquad();
}

void BiquadFilter::setQ(float q) {
    this->q = q;
    calcBiquad();
}

void BiquadFilter::setFrequency(float frequency) {
    if(frequency > sampleRate*0.5) {
        frequency = sampleRate*0.5;
    }
    this->frequency = frequency;
    this->fc = frequency / sampleRate;
    calcBiquad();
}

void BiquadFilter::setPeakGain(float peakGainDB) {
    this->peakGain = peakGainDB;
    calcBiquad();
}

void BiquadFilter::setBiquad(FilterType type, float frequency, float q, float peakGainDB) {
    this->type = type;
    this->q = q;
    this->frequency = frequency;
    this->fc = frequency / sampleRate;
    setPeakGain(peakGainDB);
}

void BiquadFilter::calcBiquad() {
    float norm;
    float v = pow(10, fabs(peakGain) / 20.0);
    float k = tan(M_PI * fc);
    switch (this->type) {
        case LOWPASS:
            norm = 1 / (1 + k / q + k * k);
            a0 = k * k * norm;
            a1 = 2 * a0;
            a2 = a0;
            b1 = 2 * (k * k - 1) * norm;
            b2 = (1 - k / q + k * k) * norm;
            break;
            
        case HIGHPASS:
            norm = 1 / (1 + k / q + k * q);
            a0 = 1 * norm;
            a1 = -2 * a0;
            a2 = a0;
            b1 = 2 * (k * k - 1) * norm;
            b2 = (1 - k / q + k * k) * norm;
            break;
            
        case BANDPASS:
            norm = 1 / (1 + k / q + k * k);
            a0 = k / q * norm;
            a1 = 0;
            a2 = -a0;
            b1 = 2 * (k * k - 1) * norm;
            b2 = (1 - k / q + k * k) * norm;
            break;
            
        case NOTCH:
            norm = 1 / (1 + k / q + k * k);
            a0 = (1 + k * k) * norm;
            a1 = 2 * (k * k - 1) * norm;
            a2 = a0;
            b1 = a1;
            b2 = (1 - k / q + k * k) * norm;
            break;
            
        case PEAK:
            if (peakGain >= 0) {    // boost
                norm = 1 / (1 + 1/q * k + k * k);
                a0 = (1 + v/q * k + k * k) * norm;
                a1 = 2 * (k * k - 1) * norm;
                a2 = (1 - v/q * k + k * k) * norm;
                b1 = a1;
                b2 = (1 - 1/q * k + k * k) * norm;
            }
            else {    // cut
                norm = 1 / (1 + v/q * k + k * k);
                a0 = (1 + 1/q * k + k * k) * norm;
                a1 = 2 * (k * k - 1) * norm;
                a2 = (1 - 1/q * k + k * k) * norm;
                b1 = a1;
                b2 = (1 - v/q * k + k * k) * norm;
            }
            break;
        case LOWSHELF:
            if (peakGain >= 0) {    // boost
                norm = 1 / (1 + sqrt(2) * k + k * k);
                a0 = (1 + sqrt(2*v) * k + v * k * k) * norm;
                a1 = 2 * (v * k * k - 1) * norm;
                a2 = (1 - sqrt(2*v) * k + v * k * k) * norm;
                b1 = 2 * (k * k - 1) * norm;
                b2 = (1 - sqrt(2) * k + k * k) * norm;
            }
            else {    // cut
                norm = 1 / (1 + sqrt(2*v) * k + v * k * k);
                a0 = (1 + sqrt(2) * k + k * k) * norm;
                a1 = 2 * (k * k - 1) * norm;
                a2 = (1 - sqrt(2) * k + k * k) * norm;
                b1 = 2 * (v * k * k - 1) * norm;
                b2 = (1 - sqrt(2*v) * k + v * k * k) * norm;
            }
            break;
        case HIGHSHELF:
            if (peakGain >= 0) {    // boost
                norm = 1 / (1 + sqrt(2) * k + k * k);
                a0 = (v + sqrt(2*v) * k + k * k) * norm;
                a1 = 2 * (k * k - v) * norm;
                a2 = (v - sqrt(2*v) * k + k * k) * norm;
                b1 = 2 * (k * k - 1) * norm;
                b2 = (1 - sqrt(2) * k + k * k) * norm;
            }
            else {    // cut
                norm = 1 / (v + sqrt(2*v) * k + k * k);
                a0 = (1 + sqrt(2) * k + k * k) * norm;
                a1 = 2 * (k * k - 1) * norm;
                a2 = (1 - sqrt(2) * k + k * k) * norm;
                b1 = 2 * (k * k - v) * norm;
                b2 = (v - sqrt(2*v) * k + k * k) * norm;
            }
            break;
    }
    
    return;
}