#ifndef LABA2_LINKEDLIST_H
#define LABA2_LINKEDLIST_H

#include <stdexcept>

template <class T>
class LinkedList {

private:
    struct Node {
        T data;
        Node *next;

        Node(T value) {
            data = value;
            next = nullptr; // чтобы он не указывад на случайный адрес памяти
        }
    };

    Node *head;
    Node *tail;
    int length;

public:
    // конструкторы
    LinkedList(const T *element, int count);
    LinkedList();
    LinkedList(const LinkedList& list);

    // деструкторы
    ~LinkedList();

    // декомпозиция
    const T& GetFirst() const;
    const T& GetLast() const;
    const T& Get(int index) const;
    Node* GetHead() const;

    LinkedList<T>* GetSubList(int startIndex, int endIndex);

    int GetLength() const;

    // Operations
    void Append(const T& element); // добавить в конец
    void Prepend(const T& element); // добавить в начало
    void InsertAt(const T& element, int index); // добавить в заданную позицию
    void RemoveAt(int index);

    LinkedList<T>* Concat(LinkedList<T> *list);
};

/*============ КОНСТРУКТОРЫ ============*/

template<class T>
LinkedList<T>::LinkedList(const T *element, int count) {
    if (count < 0)
        throw std::out_of_range("Index out of range");
    head = nullptr;
    tail = nullptr;
    length = 0;

    for (int i = 0; i < count; i++) {
        append(element[i]);
    }
}

template<class T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    tail = nullptr;
    length = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList& list) {
    head = nullptr;
    tail = nullptr;
    length = 0;

    Node *current = list.head;
    while (current != nullptr) {
        Append(current->data);
        current = current->next;
    }
}

/*============ ДЕСТРУКТОР ============*/

template<class T>
LinkedList<T>::~LinkedList() {

    Node *current = head;

    while (current != nullptr) {
        Node *next = current->next;
        delete current;
        current = next;
    }
}

/*============ ГЕТТЕРЫ ============*/

template<class T>
const T& LinkedList<T>::GetFirst() const{
    if (length == 0)
        throw std::out_of_range("Empty list");
    return head->data;
}

template<class T>
const T& LinkedList<T>::GetLast() const {
    if (length == 0)
        throw std::out_of_range("Empty list");
    return tail->data;
}

template<class T>
const T& LinkedList<T>::Get(int index) const {
    if (index < 0 || index >= length)
        throw std::out_of_range("Index out of range");

    Node *current = head;

    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

template<class T>
typename LinkedList<T>::Node* LinkedList<T>::GetHead() const {
    return head;
}

template<class T>
int LinkedList<T>::GetLength() const{
    return length;
}

template<class T>
LinkedList<T> *LinkedList<T>::GetSubList(int startIndex, int endIndex) {
    if (startIndex < 0 || startIndex >= length || startIndex > endIndex || endIndex >= length)
        throw std::out_of_range("Index out of range");

    LinkedList<T> *newList = new LinkedList<T>();

    Node *current = head;
    for (int i = 0; i < startIndex; i++) {
        current = current->next;
    }

    for (int i = startIndex; i <= endIndex; i++) {
        newList->Append(current->data);
        current = current->next;
    }

    return newList;
}

/*============ ОПЕРАЦИИ ============*/

template<class T>
void LinkedList<T>::Append(const T& element) {

    Node *newNode = new Node(element);

    if (length == 0) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }

    length++;
}

template<class T>
void LinkedList<T>::Prepend(const T& element) {

    Node *newNode = new Node(element);

    newNode->next = head;
    head = newNode;

    if (length == 0) {
        tail = newNode;
    }
    length++;
}

template<class T>
void LinkedList<T>::InsertAt(const T& element, int index) {
    if (index < 0 || index > length)
        throw std::out_of_range("Index out of range");

    if (index == 0) {
        Prepend(element);
        return;
    }
    if (index == length) {
        Append(element);
        return;
    }

    Node *prev = head;

    for (int i = 0; i < index - 1; i++) {
        prev = prev->next;
    }

    Node *newNode = new Node(element);

    newNode->next = prev->next;
    prev->next = newNode;

    length++;
}

template<class T>
void LinkedList<T>::RemoveAt(int index) {

    if (index < 0 || index >= length)
        throw std::out_of_range("Index out of range");

    if (index == 0) {
        Node *to_delete = head;
        head = head->next;

        delete to_delete;
        length--;

        if (length == 0)
            tail = nullptr;

        return;
    }

    Node *prev = head;
    for (int i = 0; i < index - 1; i++) {
        prev = prev->next;
    }

    Node *to_delete = prev->next;

    prev->next = to_delete->next;

    if (to_delete == tail) {
        tail = prev;
    }

    delete to_delete;
    length--;
}

template<class T>
LinkedList<T>* LinkedList<T>::Concat(LinkedList<T> *list) {

    LinkedList<T> *concatList = new LinkedList<T>(*this);

    Node *current = list->head;
    while (current != nullptr) {
        concatList->Append(current->data);
        current = current -> next;
    }

    return concatList;
}

#endif //LABA2_LINKEDLIST_H