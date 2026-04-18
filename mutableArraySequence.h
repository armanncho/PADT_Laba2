#ifndef LAB2_MUTABLEARRAYSEQUENCE_H
#define LAB2_MUTABLEARRAYSEQUENCE_H

#include "arraySequence.h"

template<class T>
class MutableArraySequence: public ArraySequence<T> {

public:

    MutableArraySequence(const T *items, int count);
    MutableArraySequence();
    MutableArraySequence(const MutableArraySequence &other);

    Sequence<T>* instance() override;
    Sequence<T>* create_empty_sequence() const override;
};

template<class T>
MutableArraySequence<T>::MutableArraySequence()
        : ArraySequence<T>() {}

template<class T>
MutableArraySequence<T>::MutableArraySequence(const T *items, int count)
        : ArraySequence<T>(items, count) {}

template<class T>
MutableArraySequence<T>::MutableArraySequence(const MutableArraySequence<T> &other)
        : ArraySequence<T>(other) {}

template<class T>
Sequence<T>* MutableArraySequence<T>::instance() {
    return this;
}

template<class T>
Sequence<T>* MutableArraySequence<T>::create_empty_sequence() const {
    return new MutableArraySequence<T>();
}

#endif //LAB2_MUTABLEARRAYSEQUENCE_H
