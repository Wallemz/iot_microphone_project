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

std::array <uint8_t, 20000> Microphone::read(){
    std::array <uint8_t, 20000> data; 
    for(int i = 0; i < 20000; i++){ 
        data[i] = adc_read()>>4;
        //printf("%.2f\n", data[i] * adcConvert);
        //sleep_ms(1);
    }
    return data;
}

void Microphone::readLoop(){
    while(1){
        adc_raw = adc_read();
        printf("%.2f\n", adc_raw * adcConvert);
        sleep_ms(10);
    }
}