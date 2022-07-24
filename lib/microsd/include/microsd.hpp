#pragma once

#include "../sd_card.h"
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

    UINT bw;
    char chunkID[4] = {'R', 'I', 'F', 'F'};
    uint32_t chunkSize = 36; // You Don't know this until you write your data but at a minimum it is 36 for an empty file
    char format[4] = {'W', 'A', 'V', 'E'};
    char subChunk1ID[4] = {'f', 'm', 't', ' '};
    uint32_t subChunk1Size = 16;
    uint16_t audioFormat = 1;
    uint16_t numChannels = 1;
    uint32_t sampleRate = 44100;
    uint32_t byteRate = 44100 * 2;
    uint16_t blockAlign = 2;
    uint16_t bitsPerSample = 10;
    char subChunk2ID[4] = {'d', 'a', 't', 'a'};
    uint32_t subChunk2Size = 0; // You Don't know this until you write your data

    MicroSD();
    MicroSD(std::string filename);

    bool init();
    bool write(std::string data);
    bool createWav();
    bool writeWav(uint data);
    bool read();
    void unmount();
    bool prepare2Read();
    bool finishWrite();
};
