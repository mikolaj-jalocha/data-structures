//
// Created by Mikolaj Jalocha on 30/04/2025.
//

#ifndef MAX_PRIORITY_QUEUE_DOUBLY_LINKED_LIST_H
#define MAX_PRIORITY_QUEUE_DOUBLY_LINKED_LIST_H
#include <stdexcept>


template<typename T>
struct MyNode {
    T element;
    int priority;
    MyNode *next;
    MyNode *previous;
};

template<typename T>
class MaxPriorityQueueDoublyLinkedList {
private:
    MyNode<T> *head;
    MyNode<T> *tail;
    int size;

public:
    MaxPriorityQueueDoublyLinkedList();

    MaxPriorityQueueDoublyLinkedList(const MaxPriorityQueueDoublyLinkedList<T> &other);

    ~MaxPriorityQueueDoublyLinkedList();

    int return_size() const;

    [[nodiscard]] bool is_empty() const;

    void insert(T e, int p);

    void display();

    void modify_key(T e, int p);

    T peek();

    T extract_max();

private:
    int peek_max_priority();

    int peek_min_priority();

    void push_first(T e, int p);

    void push_back(T e, int p);

    T remove_first();

    T remove(T e);

    T remove_last();
};

template<typename T>
MaxPriorityQueueDoublyLinkedList<T>::MaxPriorityQueueDoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {
}

template<typename T>
MaxPriorityQueueDoublyLinkedList<
    T>::MaxPriorityQueueDoublyLinkedList(const MaxPriorityQueueDoublyLinkedList<T> &other) : head(nullptr),
    tail(nullptr), size(0) {
    MyNode<T> *current = other.head;
    while (current != nullptr) {
        push_back(current->element, current->priority);
        current = current->next;
    }
}

template<typename T>
MaxPriorityQueueDoublyLinkedList<T>::~MaxPriorityQueueDoublyLinkedList() {
    while (!is_empty()) {
        remove_first();
    }
}

template<typename T>
int MaxPriorityQueueDoublyLinkedList<T>::return_size() const {
    return size;
}

template<typename T>
bool MaxPriorityQueueDoublyLinkedList<T>::is_empty() const {
    return size == 0;
}

template<typename T>
void MaxPriorityQueueDoublyLinkedList<T>::insert(T e, int p) {
    if (is_empty() || peek_max_priority() < p) {
        push_first(e, p);
        return;
    }

    if (peek_min_priority() > p) {
        push_back(e, p);
        return;
    }

    auto *new_node = new MyNode<T>;
    new_node->element = e;
    new_node->priority = p;
    new_node->next = nullptr;
    new_node->previous = nullptr;

    MyNode<T> *current = head;

    while (current != nullptr && current->priority >= p) {
        current = current->next;
    }

    if (current == nullptr) {
        // Append to tail
        new_node->previous = tail;
        tail->next = new_node;
        tail = new_node;
    } else {

        new_node->next = current;
        new_node->previous = current->previous;

        if (current->previous != nullptr) {
            current->previous->next = new_node;
        } else {
            head = new_node;
        }
        current->previous = new_node;
    }

    size++;
}


template<typename T>
void MaxPriorityQueueDoublyLinkedList<T>::display() {
    MyNode<T> *current = head;
    while (current) {
        std::cout << current->element << " -> ";
        current = current->next;
    }
    std::cout << "NULL\n";
}

template<typename T>
void MaxPriorityQueueDoublyLinkedList<T>::modify_key(T e, int p) {
    remove(e);
    insert(e, p);
}


template<typename T>
T MaxPriorityQueueDoublyLinkedList<T>::remove(T e) {
    if (size == 0)
        throw std::out_of_range("Queue is empty");

    if (e == this->peek()) return remove_first();
    if (e == this->tail->element) return remove_last();

    MyNode<T> *temp = head;

    while (temp != nullptr && e != temp->element) {
        temp = temp->next;
    }

    if (temp == nullptr) {
        throw std::out_of_range("Element not found");
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
T MaxPriorityQueueDoublyLinkedList<T>::remove_last() {
    if (is_empty()) return T();

    T data = tail->element;
    MyNode<T> *old_tail = tail;
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


template<typename T>
T MaxPriorityQueueDoublyLinkedList<T>::peek() {
    if (is_empty()) throw std::runtime_error("Queue is empty");
    return head->element;
}

template<typename T>
T MaxPriorityQueueDoublyLinkedList<T>::extract_max() {
    return remove_first();
}

template<typename T>
int MaxPriorityQueueDoublyLinkedList<T>::peek_max_priority() {
    if (is_empty()) throw std::runtime_error("Queue is empty");
    return head->priority;
}

template<typename T>
int MaxPriorityQueueDoublyLinkedList<T>::peek_min_priority() {
    if (is_empty()) throw std::runtime_error("Queue is empty");
    return tail->priority;
}

template<typename T>
void MaxPriorityQueueDoublyLinkedList<T>::push_first(T e, int p) {
    auto *temp = new MyNode<T>;
    temp->element = e;
    temp->priority = p;
    temp->next = nullptr;
    temp->previous = nullptr;
    if (is_empty()) {
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
void MaxPriorityQueueDoublyLinkedList<T>::push_back(T e, int p) {
    if (is_empty())
        return push_first(e, p);
    auto *temp = new MyNode<T>;
    temp->element = e;
    temp->priority = p;
    temp->previous = tail;
    tail->next = temp;
    tail = temp;
    size++;
}

template<typename T>
T MaxPriorityQueueDoublyLinkedList<T>::remove_first() {
    if (is_empty()) {
        throw std::runtime_error("Cannot remove from an empty queue");
    }

    T data = head->element;
    MyNode<T> *old_head = head;
    head = head->next;

    if (head != nullptr) {
        head->previous = nullptr;
    } else {
        tail = nullptr;
    }

    delete old_head;
    size--;

    return data;
}


#endif //MAX_PRIORITY_QUEUE_DOUBLY_LINKED_LIST_H
