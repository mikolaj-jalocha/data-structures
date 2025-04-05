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

void runStructureMenu() {
    int structureChoice;
    int operationChoice;
    std::cout<<"Choose the structure:\n1-Singly linked list\n2-Doubly linked list\n3-Array list\n";
    std::cin >> structureChoice;
    std::cout << "Choose the operation:\n1 - Push first\n2 - Push last\n3 - Push at index\n4 - Remove first\n5 - Remove last\n6 - Remove at index\n7 - Search\n";
    std::cin>>operationChoice;

    switch (structureChoice) {
            case 1: {
                ArrayList<int> arrayList;
                testsForGeneratedNumbers(arrayList, "Array List", operationChoice);
                break;
            }
            case 2: {
                SinglyLinkedList<int> SinglyLinkedList;
                testsForGeneratedNumbers(SinglyLinkedList, "Singly Linked List", operationChoice);
                break;
            }
            case 3: {
                DoublyLinkedList<int> DoublyLinkedList;
                testsForGeneratedNumbers(DoublyLinkedList, "Doubly Linked List", operationChoice);
                break;
            }
            default:
                std::cout << "Wrong choice\n";
    }
}

template<typename T>
unsigned long long performanceTests(T& structure, int operation, int n, int index) {
    //create copies of structure to perform reliable test for each one operation
    std::vector<T> copies(100, structure);
    std::string fileName= " ";

    //switch case for all methods
    switch (operation) {
        case 1: {
            auto start = std::chrono::high_resolution_clock::now();
            //loop due to the very short duration of the operation
            for (int i=0; i<100; i++) {
                copies[i].push_first(n);
            }
            auto stop= std::chrono::high_resolution_clock::now();
            auto duration = duration_cast<std::chrono::nanoseconds>(stop - start);
            return duration.count();
        }
        case 2: {
            auto start = std::chrono::high_resolution_clock::now();
            for (int i=0; i<100; i++) {
                copies[i].push_back(n);
            }
            auto stop= std::chrono::high_resolution_clock::now();
            auto duration = duration_cast<std::chrono::nanoseconds>(stop - start);
            return duration.count();
        }
        case 3: {
            auto start = std::chrono::high_resolution_clock::now();
            for (int i=0; i<100; i++) {
                copies[i].push(index, n);
            }
            auto stop= std::chrono::high_resolution_clock::now();
            auto duration = duration_cast<std::chrono::nanoseconds>(stop - start);
            return duration.count();
        }
        case 4: {
            auto start = std::chrono::high_resolution_clock::now();
            for (int i=0; i<100; i++) {
                copies[i].remove_first();
            }
            auto stop= std::chrono::high_resolution_clock::now();
            auto duration = duration_cast<std::chrono::nanoseconds>(stop - start);
            return duration.count();
        }
        case 5:
            {
                auto start = std::chrono::high_resolution_clock::now();
                for (int i=0; i<100; i++) {
                    copies[i].remove_last();
                }
                auto stop= std::chrono::high_resolution_clock::now();
                auto duration = duration_cast<std::chrono::nanoseconds>(stop - start);
                return duration.count();
            }

        case 6: {

                auto start = std::chrono::high_resolution_clock::now();
                for (int i=0; i<100; i++) {
                    copies[i].remove(index);
                }
                auto stop= std::chrono::high_resolution_clock::now();
                auto duration = duration_cast<std::chrono::nanoseconds>(stop - start);
                return duration.count();

            }
        case 7: {
            auto start = std::chrono::high_resolution_clock::now();
            for (int i=0; i<100; i++) {
                copies[i].search(n);
            }
            auto stop= std::chrono::high_resolution_clock::now();
            auto duration = duration_cast<std::chrono::nanoseconds>(stop - start);
            return duration.count();

        }
        default: {
            std::cerr << "Unknown operation" << std::endl;
            return 0;
        }
    }
};

template<typename T>
void testsForGeneratedNumbers(T& structure, const std::string& structureName, int operationChoice){
    //generate random numbers to file
    for (int i=0; i<12; i++) {
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
            structure.push_back(element);
        }
        RandomNumbersFile.close();

        std::vector<unsigned long long> resultSet;
        for (int j=0; j<3; j++) {
            int testValue=20;
            int testIndex=1;
            unsigned long long result = performanceTests(structure, operationChoice, testValue, testIndex);
            resultSet.push_back(result);
        }

        unsigned long long sum = 0;
        for (const auto& time : resultSet) {
            sum += time;
        }
        unsigned long long mean = sum / resultSet.size();
        toFile(operationChoice, structureName, mean, std::to_string(number));
    }
}