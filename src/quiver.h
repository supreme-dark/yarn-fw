/*
* quiver: class quiver controller
* SdtElectronics 2021.3
*/
#pragma once

#include "drivers/pwm.h"

class quiver{
  public:
    quiver(pwm& _lhsPWM, pwm& _rhsPWM);

    unsigned int speed(unsigned int);

    void yaw(int dir);
    void forth();

  private:

    pwm& _lhsPWM;
    pwm& _rhsPWM;
    unsigned int cur_speed;
    unsigned int def_speed;
};