#ifndef MAX_PRIORITY_QUEUE_HEAP_H
#define MAX_PRIORITY_QUEUE_HEAP_H

#include <stdexcept>

template<typename T>
struct Node {
    T e;
    int p;
};

template<typename T>
class MaxPriorityQueueHeap {
private:
    int size;
    int capacity;
    Node<T>* array;

    static int parent(int i);
    static int left(int i);
    static int right(int i);

    void heapify(int i);
    void resize();
    int find(T e);

public:
    MaxPriorityQueueHeap();
    ~MaxPriorityQueueHeap();

    void insert(T e, int p);
    T peek();
    T extract_max();
    [[nodiscard]] int return_size() const;
    [[nodiscard]]bool is_empty() const;
    void modify_key(T e, int p);
    void display();
};
template<typename T>
int MaxPriorityQueueHeap<T>::parent(const int i) {
    return (i-1)/2;
}

template<typename T>
int MaxPriorityQueueHeap<T>::left(const int i) {
    return 2*i+1;
}

template<typename T>
int MaxPriorityQueueHeap<T>::right(const int i) {
    return 2*i+2;
}

template<typename T>
MaxPriorityQueueHeap<T>::MaxPriorityQueueHeap()
    : size(0), capacity(2) {
    array = new Node<T>[capacity];
}

template<typename T>
MaxPriorityQueueHeap<T>::~MaxPriorityQueueHeap() {
    delete[] array;
}

template<typename T>
void MaxPriorityQueueHeap<T>::heapify(int i) {
    int largest = i;
    if (left(i)<size && array[left(i)].p>array[largest].p) {
        largest = left(i);
    }
    if (right(i)<size && array[right(i)].p>array[largest].p) {
        largest = right(i);
    }
    if (largest != i) {
        Node<T>  swap = array[largest];
        array[largest] = array[i];
        array[i] = swap;
        heapify(largest);
    }
}

template<typename T>
void MaxPriorityQueueHeap<T>::resize() {
    if (size >= capacity) {
        capacity *= 2;
        auto* new_array = new Node<T>[capacity];
        std::copy(array, array+size, new_array);
        delete[] array;
        array = new_array;
    }
}

template<typename T>
void MaxPriorityQueueHeap<T>::insert(T e, int p) {
    resize();
    int i = size;
    Node<T> node{e, p};
    array[size]=node;
    size++;
    while (i > 0 && array[parent(i)].p < p) {
        array[i] = array[parent(i)];
        i = parent(i);
    }
    array[i] = node;
}

template<typename T>
T MaxPriorityQueueHeap<T>::peek() {
    if (size == 0) throw std::out_of_range("Heap is empty");
    return array[0].e;
}

template<typename T>
T MaxPriorityQueueHeap<T>::extract_max() {
    if (size < 1) throw std::out_of_range("Heap is empty");
    T max = array[0].e;
    array[0] = array[size - 1];
    size--;
    heapify(0);
    return max;
}

template<typename T>
int MaxPriorityQueueHeap<T>::return_size() const {
    return size;
}

template<typename T>
bool MaxPriorityQueueHeap<T>::is_empty() const {
    return size == 0;
}

template<typename T>
int MaxPriorityQueueHeap<T>::find(T e) {
    for (int i=0;i<size;i++) {
        if (array[i].e == e) {
            return i;
        }
    }
    throw std::out_of_range("Element not found");
}

template<typename T>
void MaxPriorityQueueHeap<T>::modify_key(T e, int p) {
    int i = find(e);
    int old_p = array[i].p;
    array[i].p = p;

    if (p > old_p) {
        while (i > 0 && array[parent(i)].p < array[i].p) {
            std::swap(array[i], array[parent(i)]);
            i = parent(i);
        }
    } else if (p < old_p) {
        heapify(i);
    }
}


template<typename T>
void MaxPriorityQueueHeap<T>::display(){
    std::cout<<"Current max priority queue heap {value,priority}: ";
    for (int i = 0; i < size; i++) {
        std::cout <<"{"<<array[i].e<<", "<<array[i].p<<"}";
        if (i < size - 1) std::cout << ", ";
    }
    std::cout<<std::endl;
}

#endif // MAX_PRIORITY_QUEUE_HEAP_H
