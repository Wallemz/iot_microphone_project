#include "microphone.hpp"
//#include <stdio.h>

Microphone::Microphone(){
    adcRange = (1 << 12);
    adcVRef = 3.3;
    adcConvert = (adcVRef / (static_cast <float>(adcRange) - 1));
}

void Microphone::init(){
    DEV_Module_Init();
}

uint8_t Microphone::read(){
    auto data = std::make_unique<uint8_t>(adc_read()>>8);
    return *data;
}

void Microphone::readLoop(){
    while(1){
        adc_raw = adc_read();
        printf("%.2f\n", adc_raw * adcConvert);
        sleep_ms(10);
    }
}