cmake_minimum_required(VERSION 4.0)
project(lab2)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab2 main.cpp
        DynamicArray.h
        LinkedList.h
        "Sequence.h"
        Option.h
        ArraySequence.h
        ListSequence.h
        I_enumerator.h
        I_enumerable.h
        ImmutableArraySequence.h
        MutableArraySequence.h
        ImmutableListSequence.h
        MutableListSequence.h
        tests.cpp
)
