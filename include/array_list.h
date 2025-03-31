//
// Created by Maja Mroczek on 23.03.2025.
//

#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <iostream>

template<typename T>
class ArrayList {
private:
    T* element;
    int size;
    int capacity;
public:
    ArrayList();
    ArrayList(const ArrayList<T> &other);
    ~ArrayList();

    void display();
    [[nodiscard]] int getSize() const;
    [[nodiscard]] bool isEmpty() const;

    void doubleCapacity();
    void push_back(T newElement);
    void push_first(T newElement);
    void push(int index, T newElement);
    void remove_last();
    void remove_first();
    void remove(int index);
    int search(T sElement) const;

};
template<typename T>
ArrayList<T>::ArrayList() : element(new T[2]), size(0), capacity(2) {}

template<typename T>
ArrayList<T>::ArrayList(const ArrayList<T> &other) :
    element(new T[other.capacity]),
    size(other.size),
    capacity(other.capacity)
{
    for (int i = 0; i < size; ++i) {
        element[i] = other.element[i];
    }
}

template<typename T>
ArrayList<T>::~ArrayList() {
    delete[] element;
}

template<typename T>
void ArrayList<T>::display(){
    std::cout<<"Current array list content: ";
    for (int i = 0; i < size; i++) {
        std::cout << element[i];
        if (i < size - 1) std::cout << ", ";
    }
    std::cout<<std::endl;
}

template<typename T>
int ArrayList<T>::getSize() const {
    return size;
}

template<typename T>
bool ArrayList<T>::isEmpty() const {
    return size==0;
}

template<typename T>
    void ArrayList<T>::doubleCapacity() {
    capacity *= 2;
    T* newArray = new T[capacity];
    for (int i=0; i<size; i++) {
        newArray[i] = element[i];
    }
    delete[] element;
    element = newArray;
}

template<typename T>
void ArrayList<T>::push_back(T newElement) {
    if (size >= capacity) {
        doubleCapacity();
    }
    element[size] = newElement;
    size++;
}

template<typename T>
void ArrayList<T>::push_first(T newElement) {
    if (size>=capacity) {
        doubleCapacity();
    }
    for (int i = size; i > 0; i--) {
        element[i] = element[i - 1];
    }
    element[0]= newElement;
    size++;
}

template<typename T>
void ArrayList<T>::push(int index, T newElement) {
    if (index<0 || index>size) {
        throw std::out_of_range("Index out of range");
    }
    if (size>=capacity) {
        doubleCapacity();
    }
    for (int i = size; i > index; i--) {
        element[i] = element[i - 1];
    }
    element[index]= newElement;
    size++;
}

template<typename T>
void ArrayList<T>::remove_last() {
    if (size > 0) {
        size--;
    }
}

template<typename T>
void ArrayList<T>::remove_first() {
    if (size>0) {
        for (int i=0; i<size-1; i++) {
            element[i]=element[i+1];
        }
        size--;
    }
}

template<typename T>
void ArrayList<T>::remove(int index) {
    if (index<0 || index>=size) {
        throw std::out_of_range("Index out of range");
    }
    for (int i=index;i<size-1;i++) {
        element[i]=element[i+1];
    }
    size--;
}

template<typename T>
int ArrayList<T>::search(T sElement) const{
    for (int i = 0; i<size; i++) {
        if (sElement==element[i]) {
            return i;
        }
    }
    std::cout<<"Element not found"<<std::endl;
    return -1;
}

#endif //ARRAY_LIST_H