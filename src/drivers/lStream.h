/*
* lightSS: class light stream sensor driver
* SdtElectronics 2021.3
*/

#pragma once
#include <cstddef>

class lightSS{
  public:
    lightSS(const char* ssPath);
    const unsigned char* getFrame();
    unsigned int getSQUAL();

    ~lightSS();
  private:
    int _sensorFd;
    unsigned char buffer[8192];
    unsigned char *buftop;
    unsigned char *bufesp;
    static const unsigned char* sstrrchr(const unsigned char *start, const unsigned char *end, unsigned char token);
    static unsigned char checkSum(const unsigned char *start, const unsigned char *end);
};