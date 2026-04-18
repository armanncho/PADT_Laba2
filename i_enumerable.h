#ifndef LAB2_I_ENUMERABLE_H
#define LAB2_I_ENUMERABLE_H

#include "i_enumerator.h"

template<class T>
class IEnumerable {

public:
    virtual ~IEnumerable() = default;

    virtual IEnumerator<T>* get_enumerator() const = 0;

};

#endif //LAB2_I_ENUMERABLE_H
