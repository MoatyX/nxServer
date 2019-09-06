#include "basicIO.h"

BasicIO::BasicIO(Stream* _serial)
{
    serial = _serial;
    set_echo(true);
}

void BasicIO::set_echo(bool enabled) {
    echo = enabled;
}

void BasicIO::readInput(char** input) {
    if(!serial->available() || currIndex > 256) return;
    char _c = (char)serial->read();
    if(_c == '\r') {
        serial->println();                  //make a new line
        buffer[currIndex] = 0xb00000000;   //set the terminate character
        *input = &buffer[0];              //set the input to point to the buffer
        currIndex = 0;              //reset the buffer counter
    } else {
        if(_c == '\n') return;  //'\n' gets sent after calling Serial.Println, so avoid that
        if(echo)serial->print(_c);   //print to the screen what we are typing
        if(_c == '\b') {
            currIndex--;
            return;
        }
        buffer[currIndex] = _c;         //set the current buffer index to the the char we typed
        currIndex++;    //increment the buffer
    }
}

void BasicIO::holdingLoop(char** input) {
    while(*input == nullptr) {
        wdt_reset();
        readInput(input);
    }
}

void BasicIO::readString(char** input) {
    holdingLoop(input);
}

int BasicIO::getNumber() {
    char* output = nullptr;
    holdingLoop(&output);
    return atoi(output);
}