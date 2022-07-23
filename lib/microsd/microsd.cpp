#include "microsd.hpp"
#include <cstring>

MicroSD::MicroSD(){
    filename = "test.txt";
}

MicroSD::MicroSD(std::string file){
    filename = file;
}

bool MicroSD::init(){
    // Initialize SD card
    if (!sd_init_driver()){
        printf("ERROR: Could not initialize SD Card\r\n");
        return false;
    }
    printf("INFO: SD Initialized!\r\n");

    // Mount drive
    fr = f_mount(&fs, "0:", 1);
    if (fr != FR_OK){
        printf("ERROR: Could not mount filesystem (%d)\r\n", fr);
        return false;
    }
    return true;
}


bool MicroSD::write(std::string data){
    // String to charr arr
    int length = filename.length();
    char file[length + 1];
    strcpy(file, filename.c_str());

    // Open file for writing
    fr = f_open(&fil, file, FA_WRITE | FA_CREATE_ALWAYS);
    if(fr != FR_OK){
        printf("ERROR: Could not open file (%d)\r\n", fr);
        return false;
    }

    // Write something
    const char* cData = data.c_str();
    ret = f_printf(&fil, cData);
    if(ret < 0){
        printf("ERROR: Could not write to file (%d)\r\n", ret);
        f_close(&fil);
        return false;
    }

    // CLose file
    fr = f_close(&fil);
    if(fr != FR_OK){
        printf("ERROR: Could not close file (%d)\r\n", fr);
        return false;
    }

    return true;
}

bool MicroSD::createWav(){
    // String to charr arr
    int length = filename.length();
    char file[length + 1];
    strcpy(file, filename.c_str());

    // Open file for writing
    fr = f_open(&fil, file, FA_WRITE | FA_CREATE_ALWAYS);
    if(fr != FR_OK){
        printf("ERROR: Could not open file (%d)\r\n", fr);
        return false;
    }
    UINT bw;

    // Setting WAV Header
    /// The first 4 byte of a wav file should be the characters "RIFF" */
    char chunkID[4] = {'R', 'I', 'F', 'F'};
    fr = f_write(&fil, chunkID, sizeof(chunkID), &bw);
    if (sizeof(chunkID) != bw || fr != FR_OK)
        printf("Error in writing !\n");
    bw = 0;

    
    /// 36 + SubChunk2Size
    //uint32_t chunkSize = 36; // You Don't know this until you write your data but at a minimum it is 36 for an empty file
    char chunkSize[4] = {0,0,0,36};
    fr = f_write(&fil, chunkSize, sizeof(chunkSize), &bw);
    if (sizeof(chunkSize) != bw || fr != FR_OK)
        printf("Error in writing !\n");
    bw = 0;
    
    /// "should be characters "WAVE"
    char format[4] = {'W', 'A', 'V', 'E'};
    fr = f_write(&fil, format, sizeof(format), &bw);
    if (sizeof(format) != bw || fr != FR_OK)
        printf("Error in writing !\n");
    bw = 0;

    /// " This should be the letters "fmt ", note the space character
    char subChunk1ID[4] = {'f', 'm', 't', ' '};
    fr = f_write(&fil, subChunk1ID, sizeof(subChunk1ID), &bw);
    if (sizeof(subChunk1ID) != bw || fr != FR_OK)
        printf("Error in writing !\n");
    bw = 0;
    
    ///: For PCM == 16, since audioFormat == uint16_t
    char subChunk1Size[4] = {0,0,0,16};
    fr = f_write(&fil, subChunk1Size, sizeof(subChunk1Size), &bw);
    if (sizeof(subChunk1Size) != bw || fr != FR_OK)
        printf("Error in writing !\n");
    bw = 0;

    ///: For PCM this is 1, other values indicate compression
    char audioFormat[2] = {0,1};
    fr = f_write(&fil, audioFormat, sizeof(audioFormat), &bw);
    if (sizeof(audioFormat) != bw || fr != FR_OK)
        printf("Error in writing !\n");
    bw = 0;

    ///: Mono = 1, Stereo = 2, etc.
    char numChannels[2] = {0,1};
    fr = f_write(&fil, numChannels, sizeof(numChannels), &bw);
    if (sizeof(numChannels) != bw || fr != FR_OK)
        printf("Error in writing !\n");
    bw = 0;

    ///: Sample Rate of file
    char sampleRate[4] = {0,1,88,196}; //44100
    fr = f_write(&fil, (char*)&sampleRate, sizeof((char*)&sampleRate), &bw);
    if (sizeof((char*)&sampleRate) != bw || fr != FR_OK)
        printf("Error in writing !\n");
    bw = 0;

    ///: SampleRate * NumChannels * BitsPerSample/8
    char byteRate[4] = {1,88,136,136}; //44100*2
    fr = f_write(&fil, &byteRate, sizeof(&byteRate), &bw);
    if (sizeof(&byteRate) != bw || fr != FR_OK)
        printf("Error in writing !\n");
    bw = 0;

    ///: The number of byte for one frame NumChannels * BitsPerSample/8
    char blockAlign[2] = {0,2};
    fr = f_write(&fil, blockAlign, sizeof(blockAlign), &bw);
    if (sizeof(blockAlign) != bw || fr != FR_OK)
        printf("Error in writing !\n");
    bw = 0;

    ///: 8 bits = 8, 16 bits = 16
    char bitsPerSample[2] = {0,10};
    fr = f_write(&fil, bitsPerSample, sizeof(bitsPerSample), &bw);
    if (sizeof((char*)&bitsPerSample) != bw || fr != FR_OK)
        printf("Error in writing !\n");
    bw = 0;

    ///: Contains the letters "data"
    char subChunk2ID[4] = {'d', 'a', 't', 'a'};
    fr = f_write(&fil, subChunk2ID, sizeof(subChunk2ID), &bw);
    if (sizeof(subChunk2ID) != bw || fr != FR_OK)
        printf("Error in writing !\n");
    bw = 0;

    ///: == NumSamples * NumChannels * BitsPerSample/8  i.e. number of byte in the data.
    char bitsPerSample[4] = {0,0,0,0}; // You Don't know this until you write your data
    fr = f_write(&fil, bitsPerSample, sizeof(bitsPerSample), &bw);
    if (sizeof(bitsPerSample) != bw || fr != FR_OK)
        printf("Error in writing !\n");
    bw = 0;

    // CLose file
    fr = f_close(&fil);
    if(fr != FR_OK){
        printf("ERROR: Could not close file (%d)\r\n", fr);
        return false;
    }
}
bool MicroSD::writeWav(uint data){
    
}

bool MicroSD::read(){
    // String to charr arr
    int length = filename.length();
    char file[length + 1];
    strcpy(file, filename.c_str());

    // OPen for reading
    fr = f_open(&fil, file, FA_READ);
    if(fr != FR_OK){
        printf("ERROR: Could not openm file (%d)\r\n", fr);
        return false;
    }

    // Print
    printf("Reading from '%s':\r\n", file);
    printf("---\r\n");
    while(f_gets(buf,sizeof(buf), &fil)){
        printf(buf);
    }
    printf("\r\n---\r\n");


    // CLose file
    fr = f_close(&fil);
    if(fr != FR_OK){
        printf("ERROR: Could not close file (%d)\r\n", fr);
        return false;
    }
}

void MicroSD::unmount(){
    f_unmount("0:");
    printf("INFO: SD Unmounted!");
}
