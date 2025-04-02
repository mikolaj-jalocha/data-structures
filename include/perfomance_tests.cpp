//
// Created by majam on 02.04.2025.
//
#include "utils/write_to_file.h"
#include "performance_tests.h"
#include "singly_linked_list.h"
#include "doubly_linked_list.h"
#include "array_list.h"
#include "random_numbers_generator.h"
#include <filesystem>
#include <fstream>
#include <vector>


template<typename T>
void performanceTests(T& structure, const std::string& structureName, int operation, int n, int index) {
    //create copies of structure to perform reliable test for each one operation
    std::vector<T> copies(1000, structure);
    std::string fileName= " ";

    //switch case for all methods
    switch (operation) {
        case 1: {
            fileName = "push_first.txt";
            auto start = std::chrono::high_resolution_clock::now();
            //loop due to the very short duration of the operation
            for (int i=0; i<1000; i++) {
                copies[i].push_first(n);
            }
            auto stop= std::chrono::high_resolution_clock::now();
            auto duration = duration_cast<std::chrono::microseconds>(stop - start);
            toFile(fileName, structureName, duration.count());
            break;
        }
        case 2: {
            fileName = "push_last.txt";
            auto start = std::chrono::high_resolution_clock::now();
            for (int i=0; i<1000; i++) {
                copies[i].push_back(n);
            }
            auto stop= std::chrono::high_resolution_clock::now();
            auto duration = duration_cast<std::chrono::microseconds>(stop - start);
            toFile(fileName,structureName, duration.count());
            break;
        }
        case 3: {
            fileName = "push.txt";
            auto start = std::chrono::high_resolution_clock::now();
            for (int i=0; i<1000; i++) {
                copies[i].push(index, n);
            }
            auto stop= std::chrono::high_resolution_clock::now();
            auto duration = duration_cast<std::chrono::microseconds>(stop - start);
            toFile(fileName,structureName, duration.count());
            break;
        }
        case 4: {
            fileName = "remove_first.txt";
            auto start = std::chrono::high_resolution_clock::now();
            for (int i=0; i<1000; i++) {
                copies[i].remove_first();
            }
            auto stop= std::chrono::high_resolution_clock::now();
            auto duration = duration_cast<std::chrono::microseconds>(stop - start);
            toFile(fileName,structureName, duration.count());
            break;
        }
        case 5:
            {
                fileName = "remove_last.txt";
                auto start = std::chrono::high_resolution_clock::now();
                for (int i=0; i<1000; i++) {
                    copies[i].remove_last();
                }
                auto stop= std::chrono::high_resolution_clock::now();
                auto duration = duration_cast<std::chrono::microseconds>(stop - start);
                toFile(fileName, structureName,duration.count());
                break;
            }

        case 6: {
                fileName = "remove.txt";
                auto start = std::chrono::high_resolution_clock::now();
                for (int i=0; i<1000; i++) {
                    copies[i].remove(index);
                }
                auto stop= std::chrono::high_resolution_clock::now();
                auto duration = duration_cast<std::chrono::microseconds>(stop - start);
                toFile(fileName, structureName,duration.count());
                break;
            }
        default: {
            std::cerr << "Unknown operation" << std::endl; break;
        }
    }
};

void testsForGeneratedNumbers(){
    //initialize lists and test values
    SinglyLinkedList<int> singlyLinkedList;
    DoublyLinkedList<int> doublyLinkedList;
    ArrayList<int> arrayList;

    //generate random numbers to file
    for (int i=0; i<12; i++) {
        int testIndex=1;
        int testValue=20;
        int step= 5000;
        int number = step + i*step;
        generateRandomNumbersToFile(number);

        //read and load data to structures
        std::filesystem::path filePath = std::filesystem::current_path() / (std::to_string(number) + ".txt");
        std::ifstream RandomNumbersFile(filePath);
        if (!RandomNumbersFile) {
            std::cerr << "Error: Could not open file " << filePath << "\n";
        }
        int element;
        while (RandomNumbersFile >> element) {
            singlyLinkedList.push_back(element);
            doublyLinkedList.push_back(element);
            arrayList.push_back(element);
        }
        RandomNumbersFile.close();

        toFile("push_first.txt", std::to_string(number), 0, true);
        toFile("push_last.txt", std::to_string(number), 0, true);
        toFile("push.txt", std::to_string(number), 0, true);
        toFile("remove_first.txt", std::to_string(number), 0, true);
        toFile("remove_last.txt",std::to_string(number),0, true);
        toFile("remove.txt", std::to_string(number), 0, true);
        performanceTests(singlyLinkedList, "Singly linked list:", 1, testValue);
        performanceTests(singlyLinkedList, "Singly linked list",2, testValue);
        performanceTests(singlyLinkedList, "Singly linked list", 3, testValue, testIndex);
        performanceTests(singlyLinkedList,"Singly linked list", 4);
        performanceTests(singlyLinkedList, "Singly linked list", 5);
        performanceTests(singlyLinkedList, "Singly linked list",6, testIndex);
        performanceTests(doublyLinkedList, "Doubly linked list",1, testValue);
        performanceTests(doublyLinkedList,"Doubly linked list", 2, testValue);
        performanceTests(doublyLinkedList, "Doubly linked list",3, testValue, testIndex);
        performanceTests(doublyLinkedList, "Doubly linked list", 4);
        performanceTests(doublyLinkedList, "Doubly linked list",5);
        performanceTests(doublyLinkedList, "Doubly linked list",6, testIndex);
        performanceTests(arrayList,"Array list",  1, testValue);
        performanceTests(arrayList, "Array list", 2, testValue);
        performanceTests(arrayList, "Array list",3, testValue, testIndex);
        performanceTests(arrayList, "Array list", 4);
        performanceTests(arrayList, "Array list",5);
        performanceTests(arrayList, "Array list",6, testIndex);
    }
}