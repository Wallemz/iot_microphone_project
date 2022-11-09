#pragma once

extern "C" {
    #include "../lib/microphone/DEV_Config.h"
    #include "../lib/microphone/Debug.h"
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
    //todo Usar DMA
    void init();
    uint8_t read();
    void readLoop();
};
