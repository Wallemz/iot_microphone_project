#pragma once

#ifndef MICROPHONE_HPP
#define MICROPHONE_HPP
extern "C" {
    #include "DEV_Config.h"
    #include "Debug.h"
}
#include "pico/stdlib.h"

class Microphone{
public:
    int adcRange;
    float adcVRef;
    float adcConvert;
    uint adc_raw;

    Microphone();
    
    void init();
    void read();
    void readLoop();
};

#endif