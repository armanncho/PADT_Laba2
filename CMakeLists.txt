cmake_minimum_required(VERSION 3.20)
project(lab2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Список всех заголовочных файлов (для удобства отображения в IDE)
set(HEADERS
        DynamicArray.h
        LinkedList.h
        Sequence.h
        Option.h
        ArraySequence.h
        ListSequence.h
        I_enumerator.h
        I_enumerable.h
        ImmutableArraySequence.h
        MutableArraySequence.h
        ImmutableListSequence.h
        MutableListSequence.h
)

add_executable(lab2 main.cpp ${HEADERS})


add_executable(tests tests.cpp ${HEADERS})