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

uint Microphone::read(){
    adc_raw = adc_read();
    //printf("%.2f\n", adc_raw * adcConvert);
    sleep_ms(1);
    return adc_raw;
}

void Microphone::readLoop(){
    while(1){
        adc_raw = adc_read();
        printf("%.2f\n", adc_raw * adcConvert);
        sleep_ms(10);
    }
}