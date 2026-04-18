#ifndef LABA2_TESTS_H
#define LABA2_TESTS_H

#include <iostream>
#include <cassert>

#include "DynamicArray.h"
#include "LinkedList.h"
#include "mutableArraySequence.h"
#include "immutableArraySequence.h"
#include "mutableListSequence.h"
#include "immutableListSequence.h"
#include "Option.h"

// ==========================================
// ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ДЛЯ MAP / WHERE
// ==========================================
inline int test_multiply(const int& x) { return x * 2; }
inline bool test_is_even(const int& x) { return x % 2 == 0; }
inline int test_sum(const int& a, const int& b) { return a + b; }



// ==========================================
// 1. ТЕСТЫ БАЗОВОГО МАССИВА
// ==========================================
inline void test_dynamic_array()
{
    int initial_data[] = {10, 20, 30};
    DynamicArray<int> arr(initial_data, 3);

    assert(arr.get_size() == 3);
    assert(arr.get(0) == 10);
    assert(arr.get(2) == 30);

    arr.set(99, 1);
    assert(arr.get(1) == 99);

    arr.resize(5);
    assert(arr.get_size() == 5);
    assert(arr.get(0) == 10);

    std::cout << "[OK] DynamicArray tests passed.\n";
}



// ==========================================
// 2. ТЕСТЫ ТИПА OPTION И TRY-СЕМАНТИКИ
// ==========================================
inline void test_option()
{
    // Тест 1: Пустой Option (None)
    Option<int> emptyOpt;
    assert(emptyOpt.HasValue() == false);

    // Проверка, что при попытке взять значение из пустого Option выбрасывается ошибка
    bool caught_error = false;
    try
    {
        emptyOpt.GetValue();
    }
    catch (const std::logic_error&)
    {
        caught_error = true;
    }
    assert(caught_error == true);

    // Тест 2: Option с реальным значением (Some)
    Option<int> valOpt(42);
    assert(valOpt.HasValue() == true);
    assert(valOpt.GetValue() == 42);

    // Тест 3: Try-методы на последовательности
    int data[] = {100, 200, 300};
    MutableArraySequence<int> seq(data, 3);

    // Корректный индекс
    Option<int> validGet = seq.try_get(1);
    assert(validGet.HasValue() == true);
    assert(validGet.GetValue() == 200);

    // Выход за границы (вместо падения программы возвращает пустой Option)
    Option<int> invalidGet = seq.try_get(10);
    assert(invalidGet.HasValue() == false);

    std::cout << "[OK] Option & Try-semantics tests passed.\n";
}



// ==========================================
// 3. ТЕСТЫ MUTABLE (ИЗМЕНЯЕМОСТИ)
// ==========================================
inline void test_mutable_sequence()
{
    int data[] = {1, 2, 3};
    Sequence<int>* mutSeq = new MutableArraySequence<int>(data, 3);

    // Добавляем элемент
    Sequence<int>* resultSeq = mutSeq->append(4);

    // ПРОВЕРКА 1: Указатели ДОЛЖНЫ совпадать (это один и тот же объект)
    assert(resultSeq == mutSeq);

    // ПРОВЕРКА 2: Исходный объект ДОЛЖЕН измениться
    assert(mutSeq->get_length() == 4);
    assert(mutSeq->get(3) == 4);

    delete mutSeq;
    std::cout << "[OK] Mutable Sequence tests passed.\n";
}



// ==========================================
// 4. ТЕСТЫ IMMUTABLE (НЕИЗМЕНЯЕМОСТИ)
// ==========================================
inline void test_immutable_sequence()
{
    int data[] = {1, 2, 3};
    Sequence<int>* immutSeq = new ImmutableArraySequence<int>(data, 3);

    // Добавляем элемент
    Sequence<int>* resultSeq = immutSeq->append(4);

    // ПРОВЕРКА 1: Указатели ДОЛЖНЫ отличаться (создана копия)
    assert(resultSeq != immutSeq);

    // ПРОВЕРКА 2: Исходный объект НЕ ДОЛЖЕН измениться
    assert(immutSeq->get_length() == 3);

    // ПРОВЕРКА 3: Новый объект ДОЛЖЕН содержать изменения
    assert(resultSeq->get_length() == 4);
    assert(resultSeq->get(3) == 4);

    // Очищаем оба объекта
    delete immutSeq;
    delete resultSeq;

    std::cout << "[OK] Immutable Sequence tests passed.\n";
}



// ==========================================
// 5. ТЕСТЫ АЛГОРИТМОВ (MAP / WHERE / REDUCE)
// ==========================================
inline void test_algorithms()
{
    int data[] = {1, 2, 3, 4, 5};
    MutableArraySequence<int> seq(data, 5);

    // Map
    Sequence<int>* mapped = seq.map(test_multiply);
    assert(mapped->get(0) == 2);
    assert(mapped->get(4) == 10);
    delete mapped;

    // Where
    Sequence<int>* filtered = seq.where(test_is_even);
    assert(filtered->get_length() == 2);
    assert(filtered->get(0) == 2);
    assert(filtered->get(1) == 4);
    delete filtered;

    // Reduce
    int sum = seq.reduce(test_sum, 0);
    assert(sum == 15);

    std::cout << "[OK] Algorithms (Map/Where/Reduce) tests passed.\n";
}



// ==========================================
// ГЛАВНЫЙ ЗАПУСК ВСЕХ ТЕСТОВ
// ==========================================
inline void run_all_tests()
{
    std::cout << "=== ЗАПУСК МОДУЛЬНЫХ ТЕСТОВ ===\n";

    test_dynamic_array();
    test_option();
    test_mutable_sequence();
    test_immutable_sequence();
    test_algorithms();

    std::cout << "=== ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО ===\n";
}

#endif // LABA2_TESTS_H