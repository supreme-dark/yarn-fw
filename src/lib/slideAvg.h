/*
* guidance: template class sliding averager
* SdtElectronics 2021.3
*/

#pragma once

#include <vector>
#include "circBuf.h"

template<typename T>
class slideAvg{
  public:
    slideAvg(size_t length);

    template <typename I>
    inline T init(I begin);

    T slide(T nextVal);

  private:
    ccBuf<T> buffer;
    typename ccBuf<T>::iterator head;
    typename ccBuf<T>::iterator tail;
    T prevAvg;
};

template<typename T>
slideAvg<T>::slideAvg(size_t length): buffer(length),
                                      head(buffer.begin()),
                                      tail(buffer.end()),
                                      prevAvg(0){
}

template<typename T>
template<typename I>
T slideAvg<T>::init(I begin){
    T normVal = 0;
    do{
        normVal = static_cast<T>(*(begin++)/buffer.size());
        prevAvg += normVal;
    }while(buffer.init(normVal));
    tail = buffer.end();
    return prevAvg;
}

template<typename T>
T slideAvg<T>::slide(T nextVal){
    T nextValNorm = nextVal/buffer.size();
    T tmp = *(head++);
    *(++tail) = nextValNorm;
    return prevAvg += (nextValNorm - tmp);
}