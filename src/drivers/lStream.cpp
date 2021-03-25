#include <fcntl.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#include "lStream.h"

lightSS::lightSS(const char* ssPath): buftop(buffer + 8192),
                                      bufesp(buffer){
    /* * * * * * * * termios raw mode settings * * * * * * * * 
    * See https://www.cmrr.umn.edu/~strupp/serial.html#2_5_4 * 
    * * * * * * * * * * * for details * * * * * * * * * * * */

    _sensorFd = open(ssPath, O_RDWR | O_NOCTTY);
    //TODO: Exception handling
    struct termios sssConf;
    //get the current options
    tcgetattr(_sensorFd, &sssConf);
    //set raw input, 1 second timeout
    #ifdef _DEFAULT_SOURCE
        cfmakeraw(&sssConf);
    #else
        sssConf.c_cflag |= (CLOCAL | CREAD);
        sssConf.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
        sssConf.c_oflag &= ~OPOST;
    #endif
    cfsetispeed(&sssConf, B19200);
    sssConf.c_cc[VMIN] = 9;
    sssConf.c_cc[VTIME] = 10;

    //set the options 
    tcsetattr(_sensorFd, TCSANOW, &sssConf);
}

lightSS::~lightSS(){
    close(_sensorFd);
}

const unsigned char* lightSS::getFrame(){
    while(1){
        if(bufesp + 4096 > buftop){
            bufesp = buffer;
        }
        bufesp += read(_sensorFd, bufesp, 4096);
        const unsigned char* tail = sstrrchr(bufesp, buffer, static_cast<unsigned char>(0xaa));
        if((tail - buffer) < 8 || checkSum(tail - 6, tail - 3) != *(tail - 2)){            
            continue;                                   //spin until a complete frame received
        }

        /* * * * * * * * * * * * Packet Layout of Light Stream Sensor * * * * * * * * * * * *
        *  00     01       02         03         04         05         06       07      08  *
        * 0XFE - 0X04 - Delta_XL - Delta_XH - Delta_YL - Delta_YH - CheckSum - SQUAL - 0xAA *
        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
        return tail - 6;
    }
}

unsigned int lightSS::getSQUAL(){
    return static_cast<unsigned int>(getFrame()[5]);
}

const unsigned char* lightSS::sstrrchr(const unsigned char *start, 
                                       const unsigned char *end, 
                                             unsigned char token){
    do{
        if (*start == token){
            return start;
        }
    }while(start-- != end);
  return nullptr;
}


unsigned char lightSS::checkSum(const unsigned char *start, const unsigned char *end){
    unsigned char ret = 0;
    do{
        ret += *start;
    }while(start++ != end);
    return ret;
}
