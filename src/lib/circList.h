/*
* circList: template class circular List
* SdtElectronics 2021.4
* Well, I definitely have incorporated too much black magic in this simple crap...
* Passed memory leak test with valgrind
*/

#pragma once

#include <memory>

template<typename T, typename A>
class ccList;

template<typename T>
class ccNode{
  public:
    ccNode(const T& data, ccNode<T>* next);
    
    inline ccNode<T>* next();
    inline T& get();

  private:
    template<typename _T, typename A>
    friend class ccList;
    ccNode<T>* _next;
    T _data;
};

template<typename T>
ccNode<T>::ccNode(const T& data, ccNode<T>* next): _data(data), _next(next){

}

template<typename T>
ccNode<T>* ccNode<T>::next(){
    return _next;
}

template<typename T>
T& ccNode<T>::get(){
    return _data;
}

template<typename T, typename A = std::allocator<T> >
class ccList{
  public:
    using allocator_type  = A;
    using value_type      = typename A::value_type; 
    using reference       = typename A::reference;
    using const_reference = typename A::const_reference;
    using difference_type = typename A::difference_type;
    using size_type       = typename A::size_type;

    class iterator{ 
      public:
        using difference_type   = typename A::difference_type;
        using value_type        = typename A::value_type;
        using reference         = typename A::reference;
        using pointer           = typename A::pointer;
        using iterator_category = std::forward_iterator_tag;

        iterator();
        iterator(const ccList<T, A>& list);
        iterator(const ccList<T, A>& list, size_t offset);
        iterator(ccNode<T>* nodePtr);

        iterator& operator++();
        T& operator*() const;
        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;

      private:
        ccNode<T>* ccNodePtr;
    };

    ccList();
    ~ccList();

    void push_back(const T& data);

    inline T& front() const;
    inline T& back() const;

    inline size_t size() const;

    iterator begin() const;
    iterator end() const;

  private:  

  protected:
    size_t _size;
    std::allocator<ccNode<T> > ator;
    //Reserved for derived class implementation
    ccList(size_t size);
    ccNode<T>* head;
    ccNode<T>* tail;
    ccNode<T>* next; 
};

template<typename T, typename A>
ccList<T, A>::ccList(): _size(0),
                        ator(), 
                        head(ator.allocate(1)), 
                        tail(head), 
                        next(head){

}

template<typename T, typename A>
ccList<T, A>::ccList(size_t size): _size(size),
                        ator(), 
                        head(nullptr), 
                        tail(head), 
                        next(head){
}

template<typename T, typename A>
ccList<T, A>::~ccList(){ 
    while(_size-- != 0){
        ccNode<T>* curNode = head;
        head = curNode->next();
        curNode->~ccNode();
        ator.deallocate(curNode, 1);
    }
    ator.deallocate(next, 1);
}

template<typename T, typename A>
T& ccList<T, A>::front() const{
    return *head;
}

template<typename T, typename A>
T& ccList<T, A>::back() const{
    return *tail;
}

template<typename T, typename A>
size_t ccList<T, A>::size() const{
    return _size;
}

template<typename T, typename A>
typename ccList<T, A>::iterator ccList<T, A>::begin() const{
    return ccList<T, A>::iterator(head);
}

template<typename T, typename A>
typename ccList<T, A>::iterator ccList<T, A>::end() const{
    return ccList<T, A>::iterator(tail);
}

template<typename T, typename A>
void ccList<T, A>::push_back(const T& data){
    //Placement new
    //See https://isocpp.org/wiki/faq/dtors#memory-pools for details
    //Link the new node as the next node of the previous tail node
    tail->_next = new(next) ccNode<T>(data, head);
    //Make the new node as the current tail node
    tail = next;
    //Reserve the space for the next node
    next = ator.allocate(1);
    ++_size;
}

template<typename T, typename A>
ccList<T, A>::iterator::iterator(): ccNodePtr(nullptr){
}

template<typename T, typename A>
ccList<T, A>::iterator::iterator(const ccList<T, A>& list): ccNodePtr(list.head){
}

template<typename T, typename A>
ccList<T, A>::iterator::iterator(const ccList<T, A>& list, size_t offset): 
                                                            ccNodePtr(list.head){
    offset %= list.size();
    for(size_t i = 0; i != offset; ++i){
        ccNodePtr = ccNodePtr->next();
    }
}

template<typename T, typename A>
ccList<T, A>::iterator::iterator(ccNode<T>* nodePtr): ccNodePtr(nodePtr){
}

template<typename T, typename A>
typename ccList<T, A>::iterator& ccList<T, A>::iterator::operator++(){
    ccNodePtr = ccNodePtr->next();
    return *this;
}

template<typename T, typename A>
T& ccList<T, A>::iterator::operator*() const{
    return ccNodePtr->get();
}

template<typename T, typename A>
bool ccList<T, A>::iterator::operator==(const ccList<T, A>::iterator& other) const{
    return ccNodePtr == other.ccNodePtr;
}

template<typename T, typename A>
bool ccList<T, A>::iterator::operator!=(const ccList<T, A>::iterator& other) const{
    return ccNodePtr != other.ccNodePtr;
}