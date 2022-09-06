#pragma once

#include "../sd_card.h"
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
    char chunkID[4] = {'R', 'I', 'F', 'F'}; //4
    uint32_t chunkSize = 36; //4 You Don't know this until you write your data but at a minimum it is 36 for an empty file
    char format[4] = {'W', 'A', 'V', 'E'}; //4

    char subChunk1ID[4] = {'f', 'm', 't', ' '}; //4
    uint32_t subChunk1Size = 16; //4
    uint16_t audioFormat = 1; //2
    uint16_t numChannels = 1; //2
    uint32_t sampleRate = 44100; //4
    uint16_t bitsPerSample = 8; //2
    //uint32_t byteRate = 44100 * 2; //4
    uint32_t byteRate = sampleRate * numChannels * bitsPerSample/8;
    //uint16_t blockAlign = 2; //2
    uint16_t blockAlign = numChannels * bitsPerSample/8; //2
    
    char subChunk2ID[4] = {'d', 'a', 't', 'a'}; //4
    uint32_t subChunk2Size = 0; //4 You Don't know this until you write your data

    MicroSD();
    MicroSD(std::string filename);

    bool init();
    bool write(std::string data);
    bool createWav();
    bool writeWav(std::array <uint8_t, 20000> data);
    bool read();
    void unmount();
    bool prepare2Write();
    bool finishWrite();
};
