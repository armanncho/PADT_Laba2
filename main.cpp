#include <iostream>
#include "Sequence.h"
#include "MutableArraySequence.h"
#include "ImmutableArraySequence.h"
#include "MutableListSequence.h"
#include "ImmutableListSequence.h"

// Валидатор ввода
int ReadInt() {
    int value;
    while (true) {
        if (std::cin >> value)
            return value;
        std::cout << "Invalid input. Enter number: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}

// Функции для Map/Where/Reduce
int MultiplyBy2(const int& x) { return x * 2; }
bool IsEven(const int& x) { return x % 2 == 0; }
int Sum(const int& a, const int& b) { return a + b; }

// Меню операций
void SequenceMenu(Sequence<int>* seq) {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n===== CURRENT SEQUENCE =====\n";
        std::cout << *seq << " (Length: " << seq->GetLength() << ")\n";

        std::cout << "\n===== OPERATIONS =====\n";
        std::cout << "1  Append\n";
        std::cout << "2  Prepend\n";
        std::cout << "3  InsertAt\n";
        std::cout << "4  RemoveAt\n";
        std::cout << "5  Get by Index\n";
        std::cout << "6  GetFirst / GetLast\n";
        std::cout << "7  Subsequence\n";
        std::cout << "8  Concat with new elements\n";
        std::cout << "9  Map (*2)\n";
        std::cout << "10 Where (only even)\n";
        std::cout << "11 Reduce (Sum)\n";
        std::cout << "0  Back to Main Menu\n";

        std::cout << "\nChoice: ";
        choice = ReadInt();

        Sequence<int>* nextSeq = seq;

        try {
            switch (choice) {
                case 1: {
                    std::cout << "Value: ";
                    nextSeq = seq->Append(ReadInt());
                    break;
                }
                case 2: {
                    std::cout << "Value: ";
                    nextSeq = seq->Prepend(ReadInt());
                    break;
                }
                case 3: {
                    std::cout << "Value: "; int v = ReadInt();
                    std::cout << "Index: "; int i = ReadInt();
                    nextSeq = seq->InsertAt(v, i);
                    break;
                }
                case 4: {
                    std::cout << "Index: ";
                    nextSeq = seq->RemoveAt(ReadInt());
                    break;
                }
                case 5: {
                    std::cout << "Index: ";
                    int i = ReadInt();
                    std::cout << "Result: " << seq->Get(i) << "\n";
                    break;
                }
                case 6: {
                    std::cout << "First: " << seq->GetFirst() << "\n";
                    std::cout << "Last: " << seq->GetLast() << "\n";
                    break;
                }
                case 7: {
                    std::cout << "Start Index: "; int start = ReadInt();
                    std::cout << "End Index: "; int end = ReadInt();
                    Sequence<int>* sub = seq->GetSubSequence(start, end);
                    std::cout << "Sub: " << *sub << "\n";
                    delete sub;
                    break;
                }
                case 8: {
                    std::cout << "Count of new elements: ";
                    int count = ReadInt();
                    Sequence<int>* other = seq->CreateEmptySequence();
                    for(int i = 0; i < count; ++i) other->Append(ReadInt());
                    nextSeq = seq->Concat(*other);
                    delete other;
                    break;
                }
                case 9: {
                    nextSeq = seq->Map(MultiplyBy2);
                    break;
                }
                case 10: {
                    nextSeq = seq->Where(IsEven);
                    break;
                }
                case 11: {
                    std::cout << "Sum: " << seq->Reduce(Sum, 0) << "\n";
                    break;
                }
            }
        } catch (const std::out_of_range& e) {
            std::cout << "Error: " << e.what() << "\n";
        }

        // Если метод вернул новый объект (актуально для Immutable),
        // удаляем старый и переключаемся на новый
        if (nextSeq != seq) {
            delete seq;
            seq = nextSeq;
        }
    }
    delete seq;
}

// Фабрики создания
Sequence<int>* CreateArraySequence() {
    std::cout << "\n1. Mutable Array\n2. Immutable Array\nChoice: ";
    return (ReadInt() == 1) ? (Sequence<int>*)new MutableArraySequence<int>()
                            : (Sequence<int>*)new ImmutableArraySequence<int>();
}

Sequence<int>* CreateListSequence() {
    std::cout << "\n1. Mutable List\n2. Immutable List\nChoice: ";
    return (ReadInt() == 1) ? (Sequence<int>*)new MutableListSequence<int>()
                            : (Sequence<int>*)new ImmutableListSequence<int>();
}

int main() {
    int mainChoice = -1;
    while (mainChoice != 0) {
        std::cout << "\n===== LAB 2: SEQUENCES =====\n";
        std::cout << "1. Work with ArraySequence\n";
        std::cout << "2. Work with ListSequence\n";
        std::cout << "0. Exit\n";
        std::cout << "\nChoice: ";

        mainChoice = ReadInt();
        if (mainChoice == 1) SequenceMenu(CreateArraySequence());
        else if (mainChoice == 2) SequenceMenu(CreateListSequence());
    }
    return 0;
}