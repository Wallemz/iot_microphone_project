#pragma once
#include <stdio.h>
#include <string>
#include "wav.hpp"
#include "microphone.hpp"
#include "microsd.hpp"


class Recorder{
public:
    Recorder();
    Recorder(std::string filename);

    bool init();

    // Time in seconds
    bool startRecording(unsigned short recordingTime);
    bool stopRecording();

private:
    WAV::Header wavHeader;
    std::string filename;
    Microphone microphone;
    MicroSD microsd;

    bool createWav();

};