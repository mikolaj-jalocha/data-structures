//
// Created by Mikolaj Jalocha on 15/03/2025.
//

#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <iostream>
#include <stdexcept>

// TODO(mikolaj-jalocha): write tests

template<typename T>
struct Node {
    T element;
    Node *next;
};

template<typename T>
class SinglyLinkedList {
private:
    Node<T> *head;
    Node<T> *tail;
    int size;

public:
    SinglyLinkedList();
    ~SinglyLinkedList();

    //nondiscard here because of presence of return value.

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
SinglyLinkedList<T>::SinglyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

template<typename T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    while (!isEmpty()) {
        remove_first();
    }
}

template<typename T>
int SinglyLinkedList<T>::getSize() const {
    return size;
}

template<typename T>
bool SinglyLinkedList<T>::isEmpty() const {
    return size == 0;
}

template<typename T>
T SinglyLinkedList<T>::first() {
    return isEmpty() ? T() : head->element;
}

template<typename T>
T SinglyLinkedList<T>::last() {
    return isEmpty() ? T() : tail->element;
}

template<typename T>
void SinglyLinkedList<T>::push_first(T e) {
    auto *temp = new Node<T>;
    temp->element = e;
    temp->next = head;
    head = temp;
    if (isEmpty()) tail = head;
    size++;
}

template<typename T>
void SinglyLinkedList<T>::push(const int index, T e) {
    if (size - 1 < index)
        throw std::out_of_range("Index can't be larger than size");

    if (index == 0)
        return push_first(e);
    if (index == size - 1)
        return push_back(e);

    Node<T> *current = head;
    Node<T> *previous = head;

    for (int i = 0; i < index; i++) {
        previous = current;
        current = current->next;
    }

    auto *temp = new Node<T>;
    temp->element = e;
    previous->next = temp;
    temp->next = current;
    size++;
}

template<typename T>
void SinglyLinkedList<T>::push_back(T e) {
    auto *temp = new Node<T>;
    temp->element = e;
    temp->next = nullptr;
    if (isEmpty()) {
        head = temp;
        tail = temp;
    } else {
        tail->next = temp;
        tail = temp;
    }
    size++;
}

template<typename T>
T SinglyLinkedList<T>::remove(const int index) {
    if (size - 1 < index)
        throw std::out_of_range("Index can't be larger than size");

    if (index == 0)
        return remove_first();
    if (index == size - 1)
        return remove_last();

    Node<T> *current = head;
    Node<T> *previous = head;

    for (int i = 0; i < index; i++) {
        previous = current;
        current = current->next;
    }

    T data = current->element;
    previous->next = current->next;
    delete current;

    size--;
    return data;
}

template<typename T>
T SinglyLinkedList<T>::remove_first() {
    if (isEmpty()) return T();
    T data = head->element;
    Node<T> *old_head = head;
    head = head->next;
    delete old_head;
    size--;
    if (size == 0) tail = nullptr;
    return data;
}

template<typename T>
T SinglyLinkedList<T>::remove_last() {
    if (isEmpty()) return T();

    T data = tail->element;
    Node<T> *current = head;
    Node<T> *previous = nullptr;

    while (current->next != nullptr) {
        previous = current;
        current = current->next;
    }

    if (previous) {
        previous->next = nullptr;
        tail = previous;
    } else {
        head = nullptr;
        tail = nullptr;
    }

    delete current;
    size--;

    return data;
}

template<typename T>
void SinglyLinkedList<T>::display() {
    Node<T> *current = head;
    while (current) {
        std::cout << current->element << " -> ";
        current = current->next;
    }
    std::cout << "NULL\n";
}

#endif // SINGLY_LINKED_LIST_H
