//
// Created by Mikolaj Jalocha on 16/03/2025.
//

#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H
#include <iostream>
#include <stdexcept>

template<typename T>
struct MyDoubleNode {
    T element;
    MyDoubleNode *next;
    MyDoubleNode *previous;
};

template<typename T>
class DoublyLinkedList {
private:
    MyDoubleNode<T> *head;
    MyDoubleNode<T> *tail;
    int size;

public:
    DoublyLinkedList();

    ~DoublyLinkedList();

    [[nodiscard]] int getSize() const;

    [[nodiscard]] bool isEmpty() const;

    T first();

    T last();

    void push_first(T e);

    void push(int index, T e);

    void push_back(T e);

    T remove(int index);

    T remove_first();

    T remove_last();

    void display();
};

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    while (!isEmpty()) {
        remove_first();
    }
}

template<typename T>
int DoublyLinkedList<T>::getSize() const {
    return size;
}

template<typename T>
bool DoublyLinkedList<T>::isEmpty() const {
    return size == 0;
}

template<typename T>
T DoublyLinkedList<T>::first() {
    return isEmpty() ? T() : head->element;
}

template<typename T>
T DoublyLinkedList<T>::last() {
    return isEmpty() ? T() : tail->element;
}

template<typename T>
void DoublyLinkedList<T>::push_first(T e) {
    auto *temp = new MyDoubleNode<T>;
    temp->element = e;
    if (isEmpty()) {
        head = temp;
        tail = head;
    } else {
        temp->next = head;
        head->previous = temp;
        head = temp;
    }
    size++;
}

template<typename T>
void DoublyLinkedList<T>::push_back(T e) {
    if (isEmpty())
        return push_first(e);
    auto *temp = new MyDoubleNode<T>;
    temp->element = e;
    temp->previous = tail;
    tail->next = temp;
    tail = temp;
    size++;
}
template<typename T>
void DoublyLinkedList<T>::push(const int index, T e) {
    if (size - 1 < index)
        throw std::out_of_range("Index can't be larger than size");

    if (index == 0)
        return push_first(e);

    MyDoubleNode<T> *current = head;

    for (int i = 0; i < index-1; i++) {
           current = current->next;
    }

    auto* temp = new MyDoubleNode<T>;

    temp->element = e;
    temp->next = current->next;
    temp->previous = current;
    current->next = temp;
    size++;

}

template<typename T>
T DoublyLinkedList<T>::remove_first() {
    if (isEmpty()) return T();
    T data = head->element;
    MyDoubleNode<T>* old_head = head;
    head = head->next;
    delete old_head;
    size--;
    if (size == 0) tail = nullptr;
    return data;
}
template<typename T>
T DoublyLinkedList<T>::remove_last() {
    if (isEmpty()) return T();
    T data = tail->element;
    MyDoubleNode<T>* old_tail = tail;
    tail = tail->previous;
    tail->next = nullptr;
    delete old_tail;
    size--;
    return data;
}
template<typename T>
T DoublyLinkedList<T>::remove(const int index) {
    if (size - 1 < index)
        throw std::out_of_range("Index can't be larger than size");
    if (index == 0)
        return remove_first();
    if (index == size - 1)
        return remove_last();

    MyDoubleNode<T>* temp = head;

    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }

    T data = temp->element;

    temp->previous->next = temp->next;
    size--;

    delete temp;
    return data;
}

template<typename T>
void DoublyLinkedList<T>::display() {
    MyDoubleNode<T> *current = head;
    while (current) {
        std::cout << current->element << " -> ";
        current = current->next;
    }
    std::cout << "NULL\n";
}


#endif //DOUBLY_LINKED_LIST_H
