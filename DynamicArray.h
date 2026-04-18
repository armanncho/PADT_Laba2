#ifndef LABA2_DYNAMICARRAY_H
#define LABA2_DYNAMICARRAY_H

#include <stdexcept>

template <class T>
class DynamicArray {
private:
    T *data;
    int size;
    int capacity;

public:
    // Конструкторы
    DynamicArray(const T *items, int count);
    DynamicArray(int size);
    DynamicArray(const DynamicArray<T>& dynamicArray);

    // Деструктор
    ~DynamicArray();

    // Декомпозиция
    const T& get(int index) const;
    int get_size() const;

    // Операции
    void set(const T& value, int index);
    void resize(int newSize);
};

template<class T>
DynamicArray<T>::DynamicArray(const T *items, int count) {
    if (count < 0)
        throw std::invalid_argument("Количество элементов не может быть отрицательным");

    this->size = count;

    if (count > 0)
        capacity = count;
    else
        capacity = 1;

    data = new T[capacity];

    for (int i = 0; i < size; i++)
        data[i] = items[i];
}

template<class T>
DynamicArray<T>::DynamicArray(int size) {
    if (size < 0)
        throw std::invalid_argument("Размер не может быть отрицательным");

    this->size = size;

    if (size > 0)
        capacity = size;
    else
        capacity = 1;

    // Добавлены круглые скобки для инициализации элементов значениями по умолчанию
    data = new T[capacity]();
}

template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& dynamicArray) {
    this->size = dynamicArray.size;
    capacity = dynamicArray.capacity;

    data = new T[capacity];

    for (int i = 0; i < size; i++)
        data[i] = dynamicArray.data[i];
}

template<class T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

template<class T>
const T& DynamicArray<T>::get(int index) const{
    if (index < 0 || index >= size)
        throw std::out_of_range("Индекс выходит за границы массива");
    return data[index];
}

template<class T>
int DynamicArray<T>::get_size() const{
    return size;
}

template<class T>
void DynamicArray<T>::set(const T& value, int index) {
    if (index < 0 || index >= size)
        throw std::out_of_range("Индекс выходит за границы массива");
    data[index] = value;
}

template<class T>
void DynamicArray<T>::resize(int newSize) {
    if (newSize < 0)
        throw std::invalid_argument("Новый размер не может быть отрицательным");

    if (newSize <= capacity) {
        size = newSize;
        return;
    }

    int newCapacity = capacity;

    while (newCapacity < newSize)
        newCapacity *= 2;

    T* newData = new T[newCapacity];

    for (int i = 0; i < size; i++)
        newData[i] = data[i];

    delete[] data;
    data = newData;
    size = newSize;
    capacity = newCapacity;
}

#endif //LABA2_DYNAMICARRAY_H