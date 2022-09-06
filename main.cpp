#include "microphone.hpp"
#include "microsd.hpp"
#include <string>
#include <iostream>
#include <array>

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

    std::array <uint8_t, 20000> data;
    data = mic.read();

    sd.prepare2Write();
    sd.writeWav(data);

    std::cout << "Data recorded successfully!!";
    sd.finishWrite();
    //sd.read();
    sd.unmount();
    mic.readLoop();

    return 0;
}
