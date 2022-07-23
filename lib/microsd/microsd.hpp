#pragma once

#ifndef MICROSD_HPP
#define MICROSD_HPP

#include "sd_card.h"
#include <stdio.h>
#include <string>

class MicroSD{
public:
    FRESULT fr;
    FATFS fs;
    FIL fil;
    int ret;
    char buf[100];
    std::string filename;

    MicroSD();
    MicroSD(std::string filename);

    bool init();
    bool write(std::string data);
    bool createWav();
    bool writeWav(uint data);
    bool read();
    void unmount();
};

#endif