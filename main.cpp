#include "include/singly_linked_list.h"
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

     return 0;
}