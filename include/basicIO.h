#ifndef BASIC_IO_H
#define BASIC_IO_H
#include <Arduino.h>

//an IO class built to workaround the PlatformIO Terminal faults
class BasicIO {

public:

    BasicIO(Stream * _serial);

    //holds the main loop until the Enter key is pressed
    void readString(char** input);
    int getNumber();
    void set_echo(bool enabled);

private:

    //a function that goes into a while loop until the input has characters 
    void holdingLoop(char** input);

    //listens for input coming from the PIO terminal
    void readInput(char** input);

    char buffer[255];
    uint8_t currIndex = 0;
    Stream* serial;
    bool echo;
    bool numbersOnly;
};

#endif