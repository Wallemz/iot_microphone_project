#pragma once

#include "../lib/microsd/sd_card.h"
#include <stdio.h>
#include <string>
#include <array>

class MicroSD{
public:
    FRESULT fr;
    FATFS fs;
    FIL fil;
    int ret;
    char buf[100];
    std::string filename;
    UINT bw;

    MicroSD();

    bool init(std::string file);
    void setWritePosition(int position);

    bool write(uint16_t data);
    bool write(uint32_t data);
    bool write(char* data);

    bool read();
    void unmount();
    bool prepare2Write();
    bool finishWrite();

    // Init -> contructor
    // unmount -> destructor
    // Leer RAII

};
