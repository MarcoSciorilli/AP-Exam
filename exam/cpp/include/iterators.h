/**
 * \file iterators.h
 * \authors 
 * \brief header containing the implementation of the class iterator.
 */

#ifndef __ITERATORS_
#define __ITERATORS_

#include<memory> //unique_ptr
#include<utility> //pair

#include"node.h"

template<class N>
class iterator {

    node<N>* here{};

    public:

    iterator()=default;

    explicit iterator(node<N>* p): here{p} {}

    ~iterator()=default;

    iterator& operator++() {
        if(here) {
            if(here->right) {
                here=here->right->findLowest();
            } else {
                here = here->findUpper();
            }
        }
        return *this;
    }

    iterator operator++(int) {
        iterator old(*this);
        operator++();
        return old;
    }

    bool operator==(const iterator& other_it) {return here==other_it.here;}

    bool operator!=(const iterator& other_it) {return here!=other_it.here;}

    N& operator*() {return here->data;}

};















#endif //__ITERATORS_
