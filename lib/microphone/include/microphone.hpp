#pragma once

extern "C" {
    #include "../DEV_Config.h"
    #include "../Debug.h"
}
#include "pico/stdlib.h"
#include <array>
#include <memory>

class Microphone{
public:
    int adcRange;
    float adcVRef;
    float adcConvert;
    uint adc_raw;

    Microphone();
    
    void init();
    uint8_t read();
    void readLoop();
};
