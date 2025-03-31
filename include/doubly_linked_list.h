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

    int search(T e);
    T get(int index);

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

//TODO: potential improvement: when index is larger that size/2 start iterating from end.
template<typename T>
void DoublyLinkedList<T>::push(int index, T e) {
    if (index < 0 || index > size)
        throw std::out_of_range("Index out of range");

    if (index == 0) return push_first(e);
    if (index == size) return push_back(e);

    MyDoubleNode<T>* current = head;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }

    auto* temp = new MyDoubleNode<T>;
    temp->element = e;
    temp->next = current->next;
    temp->previous = current;
    current->next = temp;

    if (temp->next != nullptr) {
        temp->next->previous = temp;
    }

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

    if (tail) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }

    delete old_tail;
    size--;
    return data;
}



//TODO: potential improvement: when index is larger that size/2 start iterating from end.
template<typename T>
T DoublyLinkedList<T>::remove(const int index) {
    if (index < 0 || index >= size)
        throw std::out_of_range("Index out of range");

    if (index == 0) return remove_first();
    if (index == size - 1) return remove_last();

    MyDoubleNode<T>* temp = head;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }

    T data = temp->element;
    temp->previous->next = temp->next;
    if (temp->next != nullptr) {
        temp->next->previous = temp->previous;
    }

    delete temp;
    size--;
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

template<typename T>
int DoublyLinkedList<T>::search(T e) {
    MyDoubleNode<T> *current = head;
    int indexCounter = 0;
    while (current) {
        if (current->element == e) {
            return indexCounter;
        }
        indexCounter++;
        current = current->next;
    }
    return -1;
}

template<typename T>
T DoublyLinkedList<T>::get(const int index) {
    if (index < 0 || index >= size)
        throw std::out_of_range("Index out of range");

    if (index == 0) return head->element;
    if (index == size - 1) return tail->element;

    if (index > size/2) {
        MyDoubleNode<T>* temp = tail;
        for (int i = size-1; i >= 0; i--) {
            temp = temp->previous;
        }
        return temp->element;
    } else {
        MyDoubleNode<T>* temp = head;
         for (int i = 0; i < index; i++) {
             temp = temp->next;
         }
         return temp->element;
     }
}

#endif //DOUBLY_LINKED_LIST_H
