#include "microphone.hpp"
#include "microsd.hpp"
#include <string>

std::string file = "Prueba.txt";
std::string data = "Prueba rayando microSD";

int main() {
    stdio_init_all();

    Microphone mic;
    MicroSD sd(file);

    mic.init();
    sd.init();

    //sd.write(data);
    sd.createWav();
    sd.read();
    sd.unmount();
    //mic.readLoop();

    return 0;
}
