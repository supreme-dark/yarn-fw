/*
* pwm: class pwm driver
* SdtElectronics 2021.3
*/
#pragma once

class pwm{
  public:
    pwm(const char* path);

    unsigned int dutyCycle(unsigned int);
    unsigned int frequency(unsigned int);

    void enable();
    void disable();

    ~pwm();
    
  private:
    
};