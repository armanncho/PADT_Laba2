#include <iostream>
#include <cassert>
#include <stdexcept>

#include "ImmutableArraySequence.h"
#include "MutableArraySequence.h"
#include "ImmutableListSequence.h"
#include "MutableListSequence.h"
#include "Option.h"



/*============================================================================
 * 1. ТЕСТЫ ДЛЯ IMMUTABLE ARRAY SEQUENCE
 *============================================================================*/

void TestImmutableArrayAppend() {
    ImmutableArraySequence<int> seq;
    Sequence<int>* s1 = seq.Append(1);

    assert(seq.GetLength() == 0); // Проверка иммутабельности
    assert(s1->GetLength() == 1);
    assert(s1->Get(0) == 1);

    delete s1;
    std::cout << "[OK] ImmutableArray: Append" << std::endl;
}

void TestImmutableArrayPrepend() {
    ImmutableArraySequence<int> seq;
    Sequence<int>* s1 = seq.Append(2);
    Sequence<int>* s2 = s1->Prepend(1);

    assert(s1->Get(0) == 2);
    assert(s2->Get(0) == 1);
    assert(s2->Get(1) == 2);

    delete s1;
    delete s2;
    std::cout << "[OK] ImmutableArray: Prepend" << std::endl;
}

void TestImmutableArrayInsertAt() {
    ImmutableArraySequence<int> seq;
    Sequence<int>* s1 = seq.Append(1);
    Sequence<int>* s2 = s1->Append(3);
    Sequence<int>* s3 = s2->InsertAt(2, 1);

    assert(s2->GetLength() == 2);
    assert(s3->Get(0) == 1);
    assert(s3->Get(1) == 2);
    assert(s3->Get(2) == 3);

    delete s1; delete s2; delete s3;
    std::cout << "[OK] ImmutableArray: InsertAt" << std::endl;
}

void TestImmutableArrayRemoveAt() {
    ImmutableArraySequence<int> seq;
    Sequence<int>* s1 = seq.Append(1);
    Sequence<int>* s2 = s1->Append(2);
    Sequence<int>* s3 = s2->Append(3);
    Sequence<int>* result = s3->RemoveAt(1);

    assert(s3->GetLength() == 3);
    assert(result->GetLength() == 2);
    assert(result->Get(0) == 1);
    assert(result->Get(1) == 3);

    delete s1; delete s2; delete s3; delete result;
    std::cout << "[OK] ImmutableArray: RemoveAt" << std::endl;
}

/*============================================================================
 * 2. ТЕСТЫ ДЛЯ MUTABLE ARRAY SEQUENCE
 *============================================================================*/

void TestMutableArrayOperations() {
    MutableArraySequence<int> seq;

    seq.Append(1);
    seq.Append(2);
    seq.Append(3);
    assert(seq.GetLength() == 3);
    assert(seq.Get(1) == 2);

    seq.Prepend(0);
    assert(seq.Get(0) == 0);
    assert(seq.GetLength() == 4);

    seq.InsertAt(99, 2);
    assert(seq.Get(2) == 99);

    seq.RemoveAt(2);
    assert(seq.Get(2) == 2);

    assert(seq.GetFirst() == 0);
    assert(seq.GetLast() == 3);

    std::cout << "[OK] MutableArray: Core Operations" << std::endl;
}

/*============================================================================
 * 3. ТЕСТЫ ДЛЯ IMMUTABLE LIST SEQUENCE
 *============================================================================*/

void TestImmutableListFunctional() {
    ImmutableListSequence<int> seq;
    Sequence<int>* s1 = seq.Append(1);
    Sequence<int>* s2 = s1->Append(2);
    Sequence<int>* s3 = s2->Append(3);

    // Тест Map
    auto func = [](const int& x) { return x * 2; };
    Sequence<int>* mapped = s3->Map(func);
    assert(mapped->Get(0) == 2);
    assert(mapped->Get(2) == 6);

    // Тест Where
    auto pred = [](const int& x) { return x % 2 != 0; };
    Sequence<int>* filtered = s3->Where(pred);
    assert(filtered->GetLength() == 2);
    assert(filtered->Get(0) == 1);
    assert(filtered->Get(1) == 3);

    // Тест Reduce
    auto sum = [](const int& a, const int& b) { return a + b; };
    int total = s3->Reduce(sum, 0);
    assert(total == 6);

    delete s1; delete s2; delete s3; delete mapped; delete filtered;
    std::cout << "[OK] ImmutableList: Functional (Map/Where/Reduce)" << std::endl;
}

/*============================================================================
 * 4. ТЕСТЫ ДЛЯ MUTABLE LIST SEQUENCE
 *============================================================================*/

void TestMutableListConcatSub() {
    MutableListSequence<int> seq1;
    seq1.Append(1); seq1.Append(2);

    MutableListSequence<int> seq2;
    seq2.Append(3); seq2.Append(4);

    Sequence<int>* res = seq1.Concat(seq2);
    assert(res->GetLength() == 4);
    assert(res->Get(2) == 3);

    Sequence<int>* sub = res->GetSubSequence(1, 2);
    assert(sub->GetLength() == 2);
    assert(sub->Get(0) == 2);
    assert(sub->Get(1) == 3);

    delete res;
    delete sub;
    std::cout << "[OK] MutableList: Concat & Subsequence" << std::endl;
}

/*============================================================================
 * 5. ТЕСТЫ ДЛЯ OPTION (TRYGET)
 *============================================================================*/

void TestSequenceOptions() {
    MutableArraySequence<int> seq;

    // Тест пустого состояния
    Option<int> opt1 = seq.TryGetFirst();
    assert(opt1.HasValue() == false);

    seq.Append(100);
    seq.Append(200);

    // Тест успешного получения
    Option<int> opt2 = seq.TryGetFirst();
    assert(opt2.HasValue() == true);
    assert(opt2.GetValue() == 100);

    Option<int> opt3 = seq.TryGetLast();
    assert(opt3.GetValue() == 200);

    // Тест индекса
    Option<int> opt4 = seq.TryGet(1);
    assert(opt4.GetValue() == 200);

    Option<int> opt5 = seq.TryGet(10); // Некорректный индекс
    assert(opt5.HasValue() == false);

    std::cout << "[OK] Sequence: Option (TryGet) Tests" << std::endl;
}

/*============================================================================
 * ИТОГОВАЯ ФУНКЦИЯ ЗАПУСКА ВСЕХ ТЕСТОВ
 *============================================================================*/

void RunAllTests() {
    try {
        std::cout << "\n=== STARTING ALL TESTS ===\n" << std::endl;

        // Тесты Immutable Array
        TestImmutableArrayAppend();
        TestImmutableArrayPrepend();
        TestImmutableArrayInsertAt();
        TestImmutableArrayRemoveAt();

        std::cout << "--------------------------" << std::endl;

        // Тесты Mutable Array
        TestMutableArrayOperations();

        std::cout << "--------------------------" << std::endl;

        // Тесты Immutable List
        TestImmutableListFunctional();

        std::cout << "--------------------------" << std::endl;

        // Тесты Mutable List
        TestMutableListConcatSub();

        std::cout << "--------------------------" << std::endl;

        // Тесты Option
        TestSequenceOptions();

        std::cout << "\n=== ALL TESTS PASSED SUCCESSFULLY! ===\n" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "\n!!! TEST FAILED !!!" << std::endl;
        std::cerr << "Reason: " << e.what() << std::endl;
        exit(1);
    }
}
int main() {
    RunAllTests();
    return 0;
}