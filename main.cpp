#include "recorder.hpp"
#include <string>
#include <iostream>
#include <array>
#include <memory>

std::string file = "Prueba.wav";

int main() {
    printf("┬íRECORDER INIT!\r\n");
    Recorder recorder;
    stdio_init_all();

    if(!recorder.init())
        printf("Error: Init Failed!\r\n");
        return -1;

    if(!recorder.startRecording(10))
        printf("Error: Start Recording Failed!\r\n");
        return -1;
        
    if(!recorder.stopRecording())
        printf("Error: Stop Recording Failed!\r\n");
        return -1;

    return 0;
}
