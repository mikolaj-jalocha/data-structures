#include "include/singly_linked_list.h"
#include <iostream>

#include "include/doubly_linked_list.h"

using namespace std;
int main() {
     DoublyLinkedList<int> list;

     list.push_first(10);
     list.push_first(20);
     list.push_back(30);
     list.push( 1, 25);

     std::cout << "List after insertions: ";
     list.display();

     std::cout << "First element: " << list.first() << "\n";
     std::cout << "Last element: " << list.last() << "\n";

     list.remove(1);
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