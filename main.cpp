#include "microphone.hpp"
#include "microsd.hpp"
#include <string>
#include <iostream>

std::string file = "Prueba.wav";
std::string data = "Prueba rayando microSD";

int main() {
    stdio_init_all();

    Microphone mic;
    MicroSD sd(file);

    mic.init();
    std::cout << "Mic initialized successfully!!";
    sd.init();
    std::cout << "SD initialized successfully!!";
    sd.createWav();
    std::cout << "WAV Created successfully!!";
    sd.prepare2Read();
    for(int i=0; i<200; i++){
        uint data = mic.read();
        sd.writeWav(data);
    }
    std::cout << "Data recorded successfully!!";
    sd.finishWrite();
    //sd.read();
    sd.unmount();
    mic.readLoop();

    return 0;
}
