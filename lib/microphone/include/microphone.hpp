#pragma once

extern "C" {
    #include "../DEV_Config.h"
    #include "../Debug.h"
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
    uint read();
    void readLoop();
};
