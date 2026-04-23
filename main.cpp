#include <iostream>
#include "Sequence.h"
#include "MutableArraySequence.h"
#include "ImmutableArraySequence.h"
#include "MutableListSequence.h"
#include "ImmutableListSequence.h"

//
void RunAllTests();

// Безопасное чтение целых чисел
int ReadInt() {
    int value;
    while (true) {
        if (std::cin >> value) return value;
        std::cout << "Invalid input. Enter number: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}

// Функции-помощники для Map/Where/Reduce
int MultiplyBy2(const int& x) { return x * 2; }
bool IsEven(const int& x) { return x % 2 == 0; }
int Sum(const int& a, const int& b) { return a + b; }


void SequenceMenu(Sequence<int>*& seq) {
    int choice = -1;

    while (choice != 0) {
        std::cout << "\n===== SEQUENCE OPERATIONS =====\n";
        std::cout << "Current: " << *seq << " (Length: " << seq->GetLength() << ")\n";
        std::cout << "--------------------------------\n";
        std::cout << "1.  Append      2.  Prepend     3.  InsertAt\n";
        std::cout << "4.  RemoveAt    5.  Get         6.  GetFirst\n";
        std::cout << "7.  GetLast     8.  Subsequence 9.  Concat\n";
        std::cout << "10. Map (*2)    11. Where (even) 12. Reduce (sum)\n";
        std::cout << "0.  Back to Main Menu\n";
        std::cout << "Choice: ";

        choice = ReadInt();

        try {
            if (choice == 1) {
                std::cout << "Value to append: ";
                int val = ReadInt();
                Sequence<int>* newSeq = seq->Append(val);
                if (newSeq != seq) { delete seq; seq = newSeq; }
            }
            else if (choice == 2) {
                std::cout << "Value to prepend: ";
                int val = ReadInt();
                Sequence<int>* newSeq = seq->Prepend(val);
                if (newSeq != seq) { delete seq; seq = newSeq; }
            }
            else if (choice == 3) {
                std::cout << "Value: "; int val = ReadInt();
                std::cout << "Index: "; int idx = ReadInt();
                Sequence<int>* newSeq = seq->InsertAt(val, idx);
                if (newSeq != seq) { delete seq; seq = newSeq; }
            }
            else if (choice == 4) {
                std::cout << "Index to remove: ";
                int idx = ReadInt();
                Sequence<int>* newSeq = seq->RemoveAt(idx);
                if (newSeq != seq) { delete seq; seq = newSeq; }
            }
            else if (choice == 5) {
                std::cout << "Index: "; int idx = ReadInt();
                std::cout << "Value at [" << idx << "]: " << seq->Get(idx) << "\n";
            }
            else if (choice == 6) {
                std::cout << "First: " << seq->GetFirst() << "\n";
            }
            else if (choice == 7) {
                std::cout << "Last: " << seq->GetLast() << "\n";
            }
            else if (choice == 8) {
                std::cout << "Start index: "; int l = ReadInt();
                std::cout << "End index: "; int r = ReadInt();
                Sequence<int>* sub = seq->GetSubSequence(l, r);
                std::cout << "Subsequence: " << *sub << "\n";
                delete sub;
            }
            else if (choice == 9) {
                std::cout << "Enter count of elements for other sequence: ";
                int n = ReadInt();
                Sequence<int>* other = seq->CreateEmptySequence();
                std::cout << "Enter " << n << " elements: ";
                for (int i = 0; i < n; i++) other->Append(ReadInt());

                Sequence<int>* result = seq->Concat(*other);
                delete other;
                delete seq;
                seq = result;
            }
            else if (choice == 10) {
                Sequence<int>* result = seq->Map(MultiplyBy2);
                delete seq;
                seq = result;
            }
            else if (choice == 11) {
                Sequence<int>* result = seq->Where(IsEven);
                delete seq;
                seq = result;
            }
            else if (choice == 12) {
                std::cout << "Reduce (Sum) result: " << seq->Reduce(Sum, 0) << "\n";
            }
        }
        catch (const std::out_of_range& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
        catch (const std::exception& e) {
            std::cout << "Unexpected error: " << e.what() << "\n";
        }
    }
    delete seq;
}

int main() {
    RunAllTests();

    int mainChoice = -1;
    while (mainChoice != 0) {
        std::cout << "\n===== SEQUENCE MANAGER (LAB 2) =====\n";
        std::cout << "1. Mutable Array Sequence\n";
        std::cout << "\n===== SEQUENCE MANAGER (LAB 2) =====\n";
        std::cout << "1. Mutable Array Sequence\n";
        std::cout << "2. Immutable Array Sequence\n";
        std::cout << "3. Mutable List Sequence\n";
        std::cout << "4. Immutable List Sequence\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";

        mainChoice = ReadInt();
        if (mainChoice == 0) break;

        Sequence<int>* seq = nullptr;

        switch (mainChoice) {
            case 1: seq = new MutableArraySequence<int>(); break;
            case 2: seq = new ImmutableArraySequence<int>(); break;
            case 3: seq = new MutableListSequence<int>(); break;
            case 4: seq = new ImmutableListSequence<int>(); break;
            default: std::cout << "Invalid choice.\n"; continue;
        }

        SequenceMenu(seq);
    }

    std::cout << "Goodbye!\n";
    return 0;
}