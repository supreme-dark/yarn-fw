/*
* guidance: template class sliding averager
* SdtElectronics 2021.3
*/

#pragma once

#include "circBuf.h"

template <typename T>
class slideAvg{
  public:
    slideAvg(size_t length);

    T init();

    T slide(T nextVal);

  private:
    ccBuf<T> buffer;
};