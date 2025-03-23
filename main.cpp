#include "include/singly_linked_list.h"
#include "include/array_list.h"
#include <iostream>

using namespace std;
int main() {
     SinglyLinkedList<int> list;

     list.push_first(10);
     list.push_first(20);
     list.push_back(30);
     list.push(1, 25); // Insert 25 at index 1

     std::cout << "List after insertions: ";
     list.display();

     std::cout << "First element: " << list.first() << "\n";
     std::cout << "Last element: " << list.last() << "\n";

     list.remove(1); // Remove element at index 1
     std::cout << "List after removing index 1: ";
     list.display();

     list.remove_first();
     std::cout << "List after removing first element: ";
     list.display();

     list.remove_last();
     std::cout << "List after removing last element: ";
     list.display();


     // Simple tests to check if everything is working
     ArrayList<int> array;

     std::cout<<"\nArray list test"<<std::endl;
     array.push(1, 0);
     array.push(12, 1);
     array.push(8, 1);
     array.display();
     array.pushFirst(17);
     array.pushBack(24);
     array.display();
     array.push(82, 2);
     array.display();

     array.remove(3);
     array.display();
     array.removeFirst();
     array.removeLast();
     array.display();

     std::cout<<"Is the array list empty? "<<array.isEmpty()<<" Size of the array list: "<<array.getSize()<<std::endl;

     std::cout<<"What is the index of an element 12?"<<std::endl;
     std::cout<<array.search(12)<<std::endl;

     std::cout<<"What is the index of an element 37?"<<std::endl;
     std::cout<<array.search(37)<<std::endl;

     return 0;
}