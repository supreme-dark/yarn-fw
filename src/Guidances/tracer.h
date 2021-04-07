/*
* tracer: class tracer extends guidance
* SdtElectronics 2021.3
*/

#pragma once
#include "../drivers/lStream.h"
#include "../lib/slideAvg.h"
#include "guidance.h"

class tracer: public guidance{
  public:
    tracer(bool rhs, lightSS& sensor, size_t filterLen);

  private:
    //Calibrate SQUAL ripple range
    //Call before starting guidance
    void sCalibrate(quiver& subject);
    void tracerTask(quiver& subject);

    lightSS& _sensor;
    slideAvg<double> filter;

    //Upper and lower limit of SQUAL
    //Set by sCalibrate()
    unsigned int sRippleUL;
    unsigned int sRippleLL;

    //Flag indicating whether rover is deviating
    bool deviating;

    //Speed deviation with direction
    const int deviation;

    //Absolute value of speed deviation
    static constexpr int devBase = 10;

    //Margin value for SQUAL ripple
    static constexpr unsigned int sRippleMargin = 10;
};