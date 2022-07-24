#include "microsd.hpp"
#include <cstring>

MicroSD::MicroSD(){
    filename = "test.wav";
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

    // Start Writing from the beginning
    fr = f_lseek(&fil, 0);
    

    // Setting WAV Header
    /// The first 4 byte of a wav file should be the characters "RIFF" */
    fr = f_write(&fil, chunkID, sizeof(chunkID), &bw);
    if (sizeof(chunkID) != bw || fr != FR_OK)
        printf("Error in writing !\n");
    bw = 0;

    
    /// 36 + SubChunk2Size
    fr = f_write(&fil, (const BYTE*)&chunkSize, sizeof((const BYTE*)&chunkSize), &bw);
    if (sizeof((const BYTE*)&chunkSize) != bw || fr != FR_OK)
        printf("Error in writing !\n");
    bw = 0;
    
    /// "should be characters "WAVE"
    fr = f_write(&fil, format, sizeof(format), &bw);
    if (sizeof(format) != bw || fr != FR_OK)
        printf("Error in writing !\n");
    bw = 0;

    /// " This should be the letters "fmt ", note the space character
    fr = f_write(&fil, subChunk1ID, sizeof(subChunk1ID), &bw);
    if (sizeof(subChunk1ID) != bw || fr != FR_OK)
        printf("Error in writing !\n");
    bw = 0;
    
    ///: For PCM == 16, since audioFormat == uint16_t
    fr = f_write(&fil, (const BYTE*)&subChunk1Size, sizeof((const BYTE*)&subChunk1Size), &bw);
    if (sizeof((const BYTE*)&subChunk1Size) != bw || fr != FR_OK)
        printf("Error in writing !\n");
    bw = 0;

    ///: For PCM this is 1, other values indicate compression
    fr = f_write(&fil, (const BYTE*)&audioFormat, sizeof((const BYTE*)&audioFormat), &bw);
    if (sizeof((const BYTE*)&audioFormat) != bw || fr != FR_OK)
        printf("Error in writing !\n");
    bw = 0;

    ///: Mono = 1, Stereo = 2, etc.
    fr = f_write(&fil, (const BYTE*)&numChannels, sizeof((const BYTE*)&numChannels), &bw);
    if (sizeof((const BYTE*)&numChannels) != bw || fr != FR_OK)
        printf("Error in writing !\n");
    bw = 0;

    ///: Sample Rate of file
    fr = f_write(&fil, (const BYTE*)&sampleRate, sizeof((const BYTE*)&sampleRate), &bw);
    if (sizeof((const BYTE*)&sampleRate) != bw || fr != FR_OK)
        printf("Error in writing !\n");
    bw = 0;

    ///: SampleRate * NumChannels * BitsPerSample/8
    fr = f_write(&fil, (const BYTE*)&byteRate, sizeof((const BYTE*)&byteRate), &bw);
    if (sizeof((const BYTE*)&byteRate) != bw || fr != FR_OK)
        printf("Error in writing !\n");
    bw = 0;

    ///: The number of byte for one frame NumChannels * BitsPerSample/8
    fr = f_write(&fil, (const BYTE*)&blockAlign, sizeof((const BYTE*)&blockAlign), &bw);
    if (sizeof((const BYTE*)&blockAlign) != bw || fr != FR_OK)
        printf("Error in writing !\n");
    bw = 0;

    ///: 8 bits = 8, 16 bits = 16
    fr = f_write(&fil, (const BYTE*)&bitsPerSample, sizeof((const BYTE*)&bitsPerSample), &bw);
    if (sizeof((const BYTE*)&bitsPerSample) != bw || fr != FR_OK)
        printf("Error in writing !\n");
    bw = 0;

    ///: Contains the letters "data"
    fr = f_write(&fil, subChunk2ID, sizeof(subChunk2ID), &bw);
    if (sizeof(subChunk2ID) != bw || fr != FR_OK)
        printf("Error in writing !\n");
    bw = 0;

    ///: == NumSamples * NumChannels * BitsPerSample/8  i.e. number of byte in the data.
    fr = f_write(&fil, (const BYTE*)&subChunk2Size, sizeof((const BYTE*)&subChunk2Size), &bw);
    if (sizeof((const BYTE*)&subChunk2Size) != bw || fr != FR_OK)
        printf("Error in writing !\n");
    bw = 0;
    
    // CLose file
    fr = f_close(&fil);
    sleep_ms(500);

    return true;
}


bool MicroSD::prepare2Read(){
    // String to charr arr
    int length = filename.length();
    char file[length + 1];
    strcpy(file, filename.c_str());

    // Open file for writing
    fr = f_open(&fil, file, FA_WRITE | FA_OPEN_EXISTING);
    if(fr != FR_OK){
        printf("ERROR: Could not open file (%d)\r\n", fr);
        return false;
    }
    return true;
}

bool MicroSD::writeWav(uint data){
    

    //int16_t sampleValue = map(data, MIN_DATA_VALUE 0, MAX_DATA_VALUE 1023,C -32767,D 32767);
    int16_t sampleValue = (data - 0)*(1023-0)/(32767-(-32767)) + 0;

    subChunk2Size += numChannels * bitsPerSample/8;
    //wavFile.seek(40);
    fr = f_lseek(&fil, 40);
    //wavFile.write((byte*)&subChunk2Size,4);
    fr = f_write(&fil, (const BYTE*)&subChunk2Size, sizeof((const BYTE*)&subChunk2Size), &bw);

    //wavFile.seek(4);
    fr = f_lseek(&fil, 4);
    chunkSize = 36 + subChunk2Size;
    //wavFile.write((byte*)&chunkSize,4);
    fr = f_write(&fil, (const BYTE*)&chunkSize, sizeof((const BYTE*)&chunkSize), &bw);

    //wavFile.seek(wavFile.size()-1);
    fr = f_lseek(&fil, f_size(&fil));
    //wavFile.write((byte*)&sampleValue,2);
    fr = f_write(&fil, (const BYTE*)&sampleValue, sizeof((const BYTE*)&sampleValue), &bw);

    // CLose file
    f_sync (&fil);
    return true;
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
    sleep_ms(500);
    return true;
}

bool MicroSD::finishWrite(){
    // CLose file
    fr = f_close(&fil);
    sleep_ms(500);
    return true;
}

void MicroSD::unmount(){
    f_unmount("0:");
    printf("INFO: SD Unmounted!");
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
    sleep_ms(500);

    return true;
}