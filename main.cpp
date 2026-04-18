#include <iostream>
#include "sequence.h"
#include "mutableArraySequence.h"
#include "immutableArraySequence.h"
#include "mutableListSequence.h"
#include "immutableListSequence.h"

int ReadInt()
{
    int value;

    while (true)
    {
        if (std::cin >> value)
            return value;

        std::cout << "Ошибка ввода. Введите целое число: ";

        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
}



int MultiplyBy2(const int& x)
{
    return x * 2;
}



bool IsEven(const int& x)
{
    return x % 2 == 0;
}



int Sum(const int& a, const int& b)
{
    return a + b;
}



void SequenceMenu(Sequence<int>* seq)
{
    int choice = -1;

    while (choice != 0)
    {
        std::cout << "\n--- ТЕКУЩАЯ ПОСЛЕДОВАТЕЛЬНОСТЬ ---\n";
        std::cout << *seq << "\n";
        std::cout << "----------------------------------\n";
        std::cout << "1  Append\n";
        std::cout << "2  Prepend\n";
        std::cout << "3  InsertAt\n";
        std::cout << "4  RemoveAt\n";
        std::cout << "5  Get\n";
        std::cout << "6  GetFirst / GetLast\n";
        std::cout << "7  GetSubsequence\n";
        std::cout << "8  Map (*2)\n";
        std::cout << "9  Where (even)\n";
        std::cout << "10 Reduce (sum)\n";
        std::cout << "0  Назад\n";

        std::cout << "Выбор: ";
        choice = ReadInt();



        if (choice == 1)
        {
            std::cout << "Значение: ";
            int val = ReadInt();

            Sequence<int>* newSeq = seq->append(val);

            if (newSeq != seq)
            {
                delete seq;
                seq = newSeq;
            }
        }



        else if (choice == 2)
        {
            std::cout << "Значение: ";
            int val = ReadInt();

            Sequence<int>* newSeq = seq->prepend(val);

            if (newSeq != seq)
            {
                delete seq;
                seq = newSeq;
            }
        }



        else if (choice == 3)
        {
            std::cout << "Значение: ";
            int val = ReadInt();

            std::cout << "Индекс: ";
            int idx = ReadInt();

            try
            {
                Sequence<int>* newSeq = seq->insert_at(val, idx);

                if (newSeq != seq)
                {
                    delete seq;
                    seq = newSeq;
                }
            }
            catch (...)
            {
                std::cout << "Неверный индекс\n";
            }
        }



        else if (choice == 4)
        {
            std::cout << "Индекс: ";
            int idx = ReadInt();

            try
            {
                Sequence<int>* newSeq = seq->remove_at(idx);

                if (newSeq != seq)
                {
                    delete seq;
                    seq = newSeq;
                }
            }
            catch (...)
            {
                std::cout << "Неверный индекс\n";
            }
        }



        else if (choice == 5)
        {
            std::cout << "Индекс: ";
            int idx = ReadInt();

            try
            {
                std::cout << "Элемент [" << idx << "] = " << seq->get(idx) << "\n";
            }
            catch (...)
            {
                std::cout << "Неверный индекс\n";
            }
        }



        else if (choice == 6)
        {
            try
            {
                std::cout << "First: " << seq->get_first() << "\n";
                std::cout << "Last: " << seq->get_last() << "\n";
            }
            catch (...)
            {
                std::cout << "Последовательность пуста\n";
            }
        }



        else if (choice == 7)
        {
            std::cout << "Начальный индекс: ";
            int start = ReadInt();

            std::cout << "Конечный индекс: ";
            int end = ReadInt();

            try
            {
                Sequence<int>* sub = seq->get_sub_sequence(start, end);

                std::cout << "Результат: " << *sub << "\n";

                delete sub;
            }
            catch (...)
            {
                std::cout << "Неверные индексы\n";
            }
        }



        else if (choice == 8)
        {
            std::cout << "Применяем Map (*2)...\n";

            Sequence<int>* newSeq = seq->map(MultiplyBy2);

            if (newSeq != seq)
            {
                delete seq;
                seq = newSeq;
            }
            else
            {
                std::cout << "Map применен к текущему объекту (Mutable)\n";
            }
        }



        else if (choice == 9)
        {
            std::cout << "Применяем Where (четные)...\n";

            Sequence<int>* newSeq = seq->where(IsEven);

            if (newSeq != seq)
            {
                delete seq;
                seq = newSeq;
            }
            else
            {
                std::cout << "Where применен к текущему объекту (Mutable)\n";
            }
        }



        else if (choice == 10)
        {
            int result = seq->reduce(Sum, 0);

            std::cout << "Результат Reduce (сумма): " << result << "\n";
        }
    }

    delete seq;
}



Sequence<int>* CreateArraySequence()
{
    std::cout << "\nТип ArraySequence:\n";
    std::cout << "1. Mutable\n";
    std::cout << "2. Immutable\n";
    std::cout << "Выбор: ";

    int type = ReadInt();

    if (type == 1)
        return new MutableArraySequence<int>();
    else
        return new ImmutableArraySequence<int>();
}



Sequence<int>* CreateListSequence()
{
    std::cout << "\nТип ListSequence:\n";
    std::cout << "1. Mutable\n";
    std::cout << "2. Immutable\n";
    std::cout << "Выбор: ";

    int type = ReadInt();

    if (type == 1)
        return new MutableListSequence<int>();
    else
        return new ImmutableListSequence<int>();
}



int main()
{
    int choice = -1;

    while (choice != 0)
    {
        std::cout << "\n========= ГЛАВНОЕ МЕНЮ =========\n";
        std::cout << "1. Работа с ArraySequence\n";
        std::cout << "2. Работа с ListSequence\n";
        std::cout << "0. Выход\n";
        std::cout << "Выбор: ";

        choice = ReadInt();

        if (choice == 1)
        {
            Sequence<int>* seq = CreateArraySequence();
            SequenceMenu(seq);
        }

        else if (choice == 2)
        {
            Sequence<int>* seq = CreateListSequence();
            SequenceMenu(seq);
        }
    }

    return 0;
}