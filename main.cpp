#include "include/singly_linked_list.h"
#include "include/doubly_linked_list.h"
#include "include/array_list.h"
#include <vector>
#include <chrono>


//attempt to perform time tests
template<typename T>
void performance_test(T& structure, int operation, int n = 0, int index = 0) {
    //create copies of structure to perform reliable test for each one operation
    std::vector<T> copies(1000, structure);

    //switch case for all methods
    switch (operation) {
        case 1: {
            auto start = std::chrono::high_resolution_clock::now();
            //loop due to the very short duration of the operation
            for (int i=0; i<1000; i++) {
                copies[i].push_first(n);
            }
            auto stop= std::chrono::high_resolution_clock::now();
            auto duration = duration_cast<std::chrono::microseconds>(stop - start);
            std::cout << "Perfomance time: " << duration.count() << " microseconds." << std::endl;
            break;
        }
        case 2: {
            auto start = std::chrono::high_resolution_clock::now();
            for (int i=0; i<1000; i++) {
                copies[i].push_back(n);
            }
            auto stop= std::chrono::high_resolution_clock::now();
            auto duration = duration_cast<std::chrono::microseconds>(stop - start);
           std::cout << "Perfomance time: " << duration.count() << " microseconds." << std::endl;
            break;
        }
        case 3: {
            auto start = std::chrono::high_resolution_clock::now();
            for (int i=0; i<1000; i++) {
                copies[i].push(index, n);
            }
            auto stop= std::chrono::high_resolution_clock::now();
            auto duration = duration_cast<std::chrono::microseconds>(stop - start);
            std::cout << "Perfomance time: " << duration.count() << " microseconds." << std::endl;
            break;
        }
        case 4: {
            auto start = std::chrono::high_resolution_clock::now();
            for (int i=0; i<1000; i++) {
                copies[i].remove_first();
            }
            auto stop= std::chrono::high_resolution_clock::now();
            auto duration = duration_cast<std::chrono::microseconds>(stop - start);
            std::cout << "Perfomance time: " << duration.count() << " microseconds." << std::endl;
            break;
        }
        case 5:
            {
                auto start = std::chrono::high_resolution_clock::now();
                for (int i=0; i<1000; i++) {
                    copies[i].remove_last();
                }
                auto stop= std::chrono::high_resolution_clock::now();
                auto duration = duration_cast<std::chrono::microseconds>(stop - start);
                std::cout << "Perfomance time: " << duration.count() << " microseconds." << std::endl;
                break;
            }

        case 6: {
                auto start = std::chrono::high_resolution_clock::now();
                for (int i=0; i<1000; i++) {
                    copies[i].remove(index);
                }
                auto stop= std::chrono::high_resolution_clock::now();
                auto duration = duration_cast<std::chrono::microseconds>(stop - start);
                std::cout << "Perfomance time: " << duration.count() << " microseconds." << std::endl;
                break;
            }
        default: {
            std::cerr << "Unknown operation" << std::endl; break;
        }
    }
};

int main() {
    SinglyLinkedList<int> singlyLinkedList;
    DoublyLinkedList<int> doublyLinkedList;
    ArrayList<int> arrayList;

    for (int i=0; i<10; i++) {
        singlyLinkedList.push_back(i);
        doublyLinkedList.push_back(i);
        arrayList.push_back(i);
    }

    singlyLinkedList.display();
    arrayList.display();
    doublyLinkedList.display();

    constexpr int testValue=20;
    constexpr int testIndex=1;

    std::cout<<"\nTests for pushing first element\n";
    std::cout<<"Singly linked list:\n";
    performance_test(singlyLinkedList, 1, testValue);
    std::cout<<"Doubly linked list:\n";
    performance_test(doublyLinkedList, 1, testValue);
    std::cout<<"Array list:\n";
    performance_test(arrayList, 1, testValue);

    std::cout << "\nTests for pushing last element\n";
    std::cout << "Singly linked list:\n";
    performance_test(singlyLinkedList, 2, testValue);
    std::cout << "Doubly linked list:\n";
    performance_test(doublyLinkedList, 2, testValue);
    std::cout << "Array list:\n";
    performance_test(arrayList, 2, testValue);

    std::cout << "\nTests for pushing at a specific index\n";
    std::cout << "Singly linked list:\n";
    performance_test(singlyLinkedList, 3, testValue, testIndex);
    std::cout << "Doubly linked list:\n";
    performance_test(doublyLinkedList, 3, testValue, testIndex);
    std::cout << "Array list:\n";
    performance_test(arrayList, 3, testValue, testIndex);

    std::cout << "\nTests for removing first element\n";
    std::cout << "Singly linked list:\n";
    performance_test(singlyLinkedList, 4);
    std::cout << "Doubly linked list:\n";
    performance_test(doublyLinkedList, 4);
    std::cout << "Array list:\n";
    performance_test(arrayList, 4);

    std::cout << "\nTests for removing last element\n";
    std::cout << "Singly linked list:\n";
    performance_test(singlyLinkedList, 5);
    std::cout << "Doubly linked list:\n";
    performance_test(doublyLinkedList, 5);
    std::cout << "Array list:\n";
    performance_test(arrayList, 5);

    std::cout << "\nTests for removing a specific element\n";
    std::cout << "Singly linked list:\n";
    performance_test(singlyLinkedList, 6, testIndex);
    std::cout << "Doubly linked list:\n";
    performance_test(doublyLinkedList, 6, testIndex);
    std::cout << "Array list:\n";
    performance_test(arrayList, 6, testIndex);

}