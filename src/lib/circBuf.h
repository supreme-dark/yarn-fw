/*
* circList: template class circular List
* SdtElectronics 2021.4
* Holy shit, stuff did go wild when I am deriving this subclass...
* If this code is going to be reused in other projects someday,
* it would be better to devote time into rewriting it 
* Currently works fine for this project though, so no more changes yet
* Passed memory leak test with valgrind
*/

#pragma once

#include "circList.h"

template<typename T, typename A = std::allocator<T> >
class ccBuf: public ccList<T, A>{
  public:
    //Explicit specification for scope of dependent names
    //See https://stackoverflow.com/a/4010291/10627291 for details
    using ccList<T, A>::head;
    using ccList<T, A>::tail;
    using ccList<T, A>::next;
    using ccList<T, A>::ator;
    using ccList<T, A>::_size;
    using ccList<T, A>::ccList;

    ccBuf(size_t size);
    ~ccBuf();

    template<typename I>
    void init(I begin, I end);
};

template<typename T, typename A>
ccBuf<T, A>::ccBuf(size_t size): ccList<T, A>::ccList(size){
    head = ator.allocate(size);
    tail = head;
    next = ator.allocate(1);
}

template<typename T, typename A>
ccBuf<T, A>::~ccBuf(){
    ator.deallocate(head, _size);
    _size = 0;
}

template<typename T, typename A>
template<typename I>
void ccBuf<T, A>::init(I begin, I end){
    do{
        //Avoiding unsequenced modification
        ccNode<T>* tmp = tail;
        new(tmp) ccNode<T>(*begin, ++tail);
    }while(++begin != (end - 1));
    new(tail) ccNode<T>(*begin, head);
}