#include "include/performance_tests.h"
#include <iostream>

#include "include/collections/max_priority_queue_heap.h"

int main() {
    //runStructureMenu();
    //simple tests for max priority queue heap
    MaxPriorityQueueHeap<int> heap;
    
    heap.insert(1, 0);
    heap.insert(12, 1);
    heap.insert(23, 4);
    heap.insert(82, 3);
    heap.insert(8, 2);
    heap.display();

    std::cout<<"size :"<<std::endl;
    std::cout<<heap.return_size()<<std::endl;

    std::cout<<"extract max :"<<std::endl;
    std::cout<<heap.extract_max()<<std::endl;

    heap.display();
    std::cout<<"peek :"<<std::endl;
    std::cout<<heap.peek()<<std::endl;
    heap.display();

    std::cout<<"modify 12 to priority 5\n";
    heap.modify_key(12,5);
    heap.display();
}
