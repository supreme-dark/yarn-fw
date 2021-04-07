#include <cstdlib>
#include <cstdio>
#include <vector>
#include "../src/drivers/lStream.h"
#include "../src/lib/slideAvg.h"

lightSS sss("/dev/ttyS7");

void printFrame(const unsigned char* start){
    for(size_t d = 0; d != 7; ++d){
        printf("%02X", start[d]);
    }
    printf("\n");
}

int main(int argc, char** argv){
    const int len = atoi(argv[1]);
    slideAvg<double> sv(len);
    std::vector<double> v(len);
    for(double& i: v){
        i = static_cast<double>(sss.getSQUAL());
    }
    sv.init(v.begin());
    while(1){
        printf("%f\n", sv.slide(sss.getSQUAL()));
    }
}

#if 0
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

unsigned int getSQUAL(int fd){
    char pre, ret;
    while(read(fd, &pre, 1)){
        if(pre != 0xFE){            //if header is not encountered
            continue;               //spin until a header arrives.
        }

        /* * * * * * * * * * * * Packet Layout of Light Stream Sensor * * * * * * * * * * * *
        *  00     01       02         03         04         05         06       07      08  *
        * 0XFE - 0X04 - Delta_XL - Delta_XH - Delta_YL - Delta_YH - CheckSum - SQUAL - 0xAA *
        * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

        char buf[8];
        read(fd, buf, 8);
        ret = buf[6];
    }
    return static_cast<unsigned int>(ret);
}

int main(){
    while(1){
        printf("%u\n", getSQUAL(STDIN_FILENO));
    }
}
#endif