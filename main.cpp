#include "microphone.hpp"
#include "microsd.hpp"
#include <string>
#include <iostream>
#include <array>
#include <memory>

std::string file = "Prueba.wav";
std::string data = "Prueba rayando microSD";

int main() {
    int size = 200;
    stdio_init_all();

    Microphone mic;
    MicroSD sd(file);

    mic.init();
    printf("Mic initialized successfully!!");
    sd.init();
    std::cout << "SD initialized successfully!!";
    sd.createWav();
    std::cout << "WAV Created successfully!!";
    uint8_t data;
    sd.prepare2Write();
    for(unsigned long int i = 0; i<8000; i++){
        data = mic.read();
        sd.writeWav(data);
    }
    sd.printWav();
    std::cout << "Data recorded successfully!!";
    sd.finishWrite();
    //sd.read();
    sd.unmount();
    mic.readLoop();

    return 0;
}
