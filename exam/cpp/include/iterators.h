#include<memory> //unique_ptr
#include<utility> //pair

#include "node.h"

template<class N>
class iterator {
    N* current;

public:
    iterator() = default;

    iterator(N* n) noexcept : current{n} {}

    ~iterator() = default;

    
};