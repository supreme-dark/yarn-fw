/*
* tracer: class tracer extends guidance
* SdtElectronics 2021.3
*/

#pragma once
#include "../drivers/lStream.h"
#include "guidance.h"

class tracer: public guidance{
  public:
    tracer(bool rhs, lightSS& ssLhs, lightSS& ssRhs);

  private:
    void tracerTask(quiver& subject);

    lightSS& ssl;
    lightSS& ssr;
    //Speed deviation with direction
    const int deviation;

    //Absolute value of speed deviation
    static constexpr int devBase = 10;
    static unsigned int getSQUAL(int fd);
};