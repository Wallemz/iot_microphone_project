#pragma once

extern "C" {
    #include "../DEV_Config.h"
    #include "../Debug.h"
}
#include "pico/stdlib.h"
#include <array>

class Microphone{
public:
    int adcRange;
    float adcVRef;
    float adcConvert;
    uint adc_raw;

    Microphone();
    
    void init();
    std::array <uint8_t, 20000> read();
    void readLoop();
};
