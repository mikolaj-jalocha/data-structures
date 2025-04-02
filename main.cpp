#include "include/singly_linked_list.h"
#include "include/doubly_linked_list.h"
#include "include/array_list.h"
#include "include/random_numbers_generator.h"
#include <filesystem>
#include <fstream>
#include <vector>
#include <chrono>

//TODO: enhance writing to file logic
//TODO: improve overall structure and maybe move performance tests to separate file

void toFile(const std::string& fileName, long long duration) {
    std::ofstream file(fileName, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << fileName << std::endl;
    }
    file << duration << "\n";
    file.close();
}

//attempt to perform time tests
template<typename T>
void performance_test(T& structure, const std::string& fileName, int operation, int n = 0, int index = 0) {
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
            
            // leaving this line now just to make sure writing to files works properly 
            std::cout << "Perfomance time: " << duration.count() << " microseconds." << std::endl;
            
            toFile(fileName, duration.count());
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
            toFile(fileName, duration.count());
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
            toFile(fileName, duration.count());
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
            toFile(fileName, duration.count());
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
                toFile(fileName, duration.count());
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
                toFile(fileName, duration.count());
                break;
            }
        default: {
            std::cerr << "Unknown operation" << std::endl; break;
        }
    }
};


int main() {
    //initialize lists and test values
    SinglyLinkedList<int> singlyLinkedList;
    DoublyLinkedList<int> doublyLinkedList;
    ArrayList<int> arrayList;

    constexpr int testValue=20;
    constexpr int testIndex=1;

    //generate random numbers to file
    for (int i=0; i<10; i++) {
        int step= 5000;
        generateRandomNumbersToFile((5000 + i*step));
    }

    //read and load data to structures
    std::filesystem::path filePath = std::filesystem::current_path() / "5000.txt";
    std::ifstream RandomNumbersFile(filePath);
    if (!RandomNumbersFile) {
        std::cerr << "Error: Could not open file " << filePath << "\n";
        return 1;
    }

    int element;
    while (RandomNumbersFile >> element) {
        singlyLinkedList.push_back(element);
        doublyLinkedList.push_back(element);
        arrayList.push_back(element);
    }
    RandomNumbersFile.close();

    // leaving this for now just to make sure writing to files works properly
    std::cout<<"\nTests for pushing first element\n";
    std::cout<<"Singly linked list:\n";
    performance_test(singlyLinkedList, "push_first.txt", 1, testValue);
    std::cout<<"Doubly linked list:\n";
    performance_test(doublyLinkedList, "push_first.txt",1, testValue);
    std::cout<<"Array list:\n";
    performance_test(arrayList,"push_first.txt",  1, testValue);

    std::cout << "\nTests for pushing last element\n";
    std::cout << "Singly linked list:\n";
    performance_test(singlyLinkedList, "push_back.txt",2, testValue);
    std::cout << "Doubly linked list:\n";
    performance_test(doublyLinkedList,"push_back.txt", 2, testValue);
    std::cout << "Array list:\n";
    performance_test(arrayList, "push_back.txt", 2, testValue);

    std::cout << "\nTests for pushing at a specific index\n";
    std::cout << "Singly linked list:\n";
    performance_test(singlyLinkedList, "push.txt", 3, testValue, testIndex);
    std::cout << "Doubly linked list:\n";
    performance_test(doublyLinkedList, "push.txt",3, testValue, testIndex);
    std::cout << "Array list:\n";
    performance_test(arrayList, "push.txt",3, testValue, testIndex);

    std::cout << "\nTests for removing first element\n";
    std::cout << "Singly linked list:\n";
    performance_test(singlyLinkedList,"remove_first.txt", 4);
    std::cout << "Doubly linked list:\n";
    performance_test(doublyLinkedList, "remove_first.txt", 4);
    std::cout << "Array list:\n";
    performance_test(arrayList, "remove_first.txt", 4);

    std::cout << "\nTests for removing last element\n";
    std::cout << "Singly linked list:\n";
    performance_test(singlyLinkedList, "remove_last.txt", 5);
    std::cout << "Doubly linked list:\n";
    performance_test(doublyLinkedList, "remove_last.txt",5);
    std::cout << "Array list:\n";
    performance_test(arrayList, "remove_last.txt",5);

    std::cout << "\nTests for removing a specific element\n";
    std::cout << "Singly linked list:\n";
    performance_test(singlyLinkedList, "remove.txt",6, testIndex);
    std::cout << "Doubly linked list:\n";
    performance_test(doublyLinkedList, "remove.txt",6, testIndex);
    std::cout << "Array list:\n";
    performance_test(arrayList, "remove.txt",6, testIndex);

}