#include "recorder.hpp"
#include <cstring>
#include <stdio.h>

Recorder::Recorder(){
    filename = "test.wav";
}

Recorder::Recorder(std::string filename){
    this->filename = filename;
}

bool Recorder::init() {
    microphone.init();
    if(!microsd.init(filename))
        return false;
    return true;
}

bool Recorder::startRecording(unsigned short recordingTime) {
    createWav();
    return true;
}

bool Recorder::stopRecording(){
    microsd.unmount();
    microphone.readLoop();
    return true;
}

bool Recorder::createWav(){
    if(!microsd.prepare2Write())
        return false;
    microsd.setWritePosition(0);
    microsd.write(wavHeader.chunkID);
    microsd.write(wavHeader.chunkSize);
    microsd.write(wavHeader.format);
    microsd.write(wavHeader.subChunk1ID);
    microsd.write(wavHeader.subChunk1Size);
    microsd.write(wavHeader.audioFormat);
    microsd.write(wavHeader.numChannels);
    microsd.write(wavHeader.sampleRate);
    microsd.write(wavHeader.byteRate);
    microsd.write(wavHeader.blockAlign);
    microsd.write(wavHeader.bitsPerSample);
    microsd.write(wavHeader.subChunk2ID);
    microsd.write(wavHeader.subChunk2Size);
    microsd.finishWrite();
    return true;
}
