#ifndef LABA2_LINKEDLIST_H
#define LABA2_LINKEDLIST_H

#include <stdexcept>
#include "I_enumerator.h"

// 1. Предварительное объявление класса
template <class T> class LinkedList;

// 2. Класс итератора для списка
template<class T>
class ListEnumerator : public IEnumerator<T> {
private:
    const void* current;

public:
    ListEnumerator(const LinkedList<T>* list);

    bool has_more_elements() const override;
    const T& next() override;
};

// 3. Основной класс LinkedList
template <class T>
class LinkedList {
private:
    struct Node {
        T data;
        Node *next;

        Node(T value) : data(value), next(nullptr) {}
    };

    Node *head;
    Node *tail;
    int length;

    // Делаем итератор другом, чтобы он видел структуру Node и head
    friend class ListEnumerator<T>;

public:
    // Constructors
    LinkedList();
    LinkedList(const T *element, int count);
    LinkedList(const LinkedList<T>& list);

    // Destructor
    ~LinkedList();

    // Decomposition (Обновленные имена)
    const T& GetFirst() const;
    const T& GetLast() const;
    const T& Get(int index) const;
    int GetLength() const;

    // Operations
    void Append(const T& element);
    void Prepend(const T& element);
    void InsertAt(const T& element, int index);
    void RemoveAt(int index);

    LinkedList<T>* Concat(LinkedList<T> *list);
};

/*============ РЕАЛИЗАЦИЯ ИТЕРАТОРА ============*/

template<class T>
ListEnumerator<T>::ListEnumerator(const LinkedList<T>* list) {
    this->current = list->head;
}

template<class T>
bool ListEnumerator<T>::has_more_elements() const {
    return current != nullptr;
}

template<class T>
const T& ListEnumerator<T>::next() {
    if (!has_more_elements())
        throw std::out_of_range("ListEnumerator::next");

    // Приводим void* обратно к Node* для доступа к данным
    const auto* node = static_cast<const typename LinkedList<T>::Node*>(current);
    const T& value = node->data;
    current = node->next;
    return value;
}

/*============ РЕАЛИЗАЦИЯ МЕТОДОВ СПИСКА ============*/

template<class T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), length(0) {}

template<class T>
LinkedList<T>::LinkedList(const T *element, int count) : LinkedList() {
    if (count < 0) throw std::out_of_range("Count < 0");
    for (int i = 0; i < count; i++) Append(element[i]);
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) : LinkedList() {
    Node *current = list.head;
    while (current != nullptr) {
        Append(current->data);
        current = current->next;
    }
}

template<class T>
LinkedList<T>::~LinkedList() {
    Node *current = head;
    while (current != nullptr) {
        Node *next = current->next;
        delete current;
        current = next;
    }
}

template<class T>
const T& LinkedList<T>::GetFirst() const {
    if (length == 0) throw std::out_of_range("Empty list");
    return head->data;
}

template<class T>
const T& LinkedList<T>::GetLast() const {
    if (length == 0) throw std::out_of_range("Empty list");
    return tail->data;
}

template<class T>
const T& LinkedList<T>::Get(int index) const {
    if (index < 0 || index >= length) throw std::out_of_range("Index out of range");
    Node *current = head;
    for (int i = 0; i < index; i++) current = current->next;
    return current->data;
}

template<class T>
int LinkedList<T>::GetLength() const {
    return length;
}

template<class T>
void LinkedList<T>::Append(const T& element) {
    Node *newNode = new Node(element);
    if (length == 0) {
        head = tail = newNode;
    } else {
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
    if (length == 0) tail = newNode;
    length++;
}

template<class T>
void LinkedList<T>::InsertAt(const T& element, int index) {
    if (index < 0 || index > length) throw std::out_of_range("Index out of range");
    if (index == 0) { Prepend(element); return; }
    if (index == length) { Append(element); return; }

    Node *prev = head;
    for (int i = 0; i < index - 1; i++) prev = prev->next;
    Node *newNode = new Node(element);
    newNode->next = prev->next;
    prev->next = newNode;
    length++;
}

template<class T>
void LinkedList<T>::RemoveAt(int index) {
    if (index < 0 || index >= length) throw std::out_of_range("Index out of range");
    if (index == 0) {
        Node *toDelete = head;
        head = head->next;
        delete toDelete;
        length--;
        if (length == 0) tail = nullptr;
        return;
    }
    Node *prev = head;
    for (int i = 0; i < index - 1; i++) prev = prev->next;
    Node *toDelete = prev->next;
    prev->next = toDelete->next;
    if (toDelete == tail) tail = prev;
    delete toDelete;
    length--;
}

template<class T>
LinkedList<T>* LinkedList<T>::Concat(LinkedList<T> *list) {
    LinkedList<T> *concatList = new LinkedList<T>(*this);
    Node *current = list->head;
    while (current != nullptr) {
        concatList->Append(current->data);
        current = current->next;
    }
    return concatList;
}

#endif //LABA2_LINKEDLIST_H