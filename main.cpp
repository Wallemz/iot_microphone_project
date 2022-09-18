#include "recorder.hpp"
#include <string>
#include <iostream>
#include <array>
#include <memory>

std::string file = "Prueba.wav";
std::string data = "Prueba rayando microSD";

int main() {
    printf("Mic initialized successfully!!");
    std::cout << "SD initialized successfully!!";
    Recorder recorder;
    // int size = 200;
    stdio_init_all();
    recorder.init();
    recorder.startRecording(10);
    recorder.stopRecording();

    // Microphone mic;
    // MicroSD sd(file);

    // mic.init();
    
    // sd.createWav();
    // std::cout << "WAV Created successfully!!";
    // uint8_t data;
    // sd.prepare2Write();
    // for(unsigned long int i = 0; i<8000; i++){
    //     data = mic.read();
    //     sd.writeWav(data);
    // }
    // sd.printWav();
    // std::cout << "Data recorded successfully!!";
    // sd.finishWrite();
    // //sd.read();
    // sd.unmount();
    // mic.readLoop();

    return 0;
}
