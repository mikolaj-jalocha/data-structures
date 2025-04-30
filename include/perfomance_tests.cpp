//
// Created by majam on 02.04.2025.
//
#include "utils/write_to_file.h"
#include "performance_tests.h"
#include "collections/singly_linked_list.h"
#include "collections/doubly_linked_list.h"
#include "collections/array_list.h"
#include "utils/random_numbers_generator.h"
#include <filesystem>
#include <fstream>
#include <vector>

int runStructureMenu() {

    //generate files with data sets
    for (int i=0; i<12; i++) {
        constexpr int step= 5000;
        const int number = step + i*step;
        generateRandomNumbersToFile(number, "_1");
        generateRandomNumbersToFile(number, "_2");
        generateRandomNumbersToFile(number, "_3");
    }

    while (true) {
        int structureChoice;
        int operationChoice;
        std::cout<<"Choose the structure:\n1-Array list\n2-Singly linked list\n3-Doubly linked list\n4-All tests at once\n0-Exit\n";
        std::cin >> structureChoice;
        if (structureChoice == 0) return 0;
        if (structureChoice !=4) {
            std::cout << "Choose the operation:\n1 - Push first\n2 - Push last\n3 - Push at index\n4 - Remove first\n5 - Remove last\n6 - Remove at index\n7 - Search\n";
            std::cin>>operationChoice;
        }
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
            case 4: {
                for (int i=1; i<=7; i++) {
                    ArrayList<int> arrayList;
                    testsForGeneratedNumbers(arrayList, "Array List", i);
                    SinglyLinkedList<int> SinglyLinkedList;
                    testsForGeneratedNumbers(SinglyLinkedList, "Singly Linked List", i);
                    DoublyLinkedList<int> DoublyLinkedList;
                    testsForGeneratedNumbers(DoublyLinkedList, "Doubly Linked List", i);
                }
            }
            default:
                std::cout << "Wrong choice\n";
                break;
        }
    }
}

template<typename T>
unsigned long long performanceTests(T& structure, int operation, int n, int index) {
    //create copies of structure to perform reliable test for each one operation
    int REPETITION = 100;
    std::vector<T> copies(REPETITION, structure);
    std::string fileName= " ";

    //switch case for all methods
    switch (operation) {
        case 1: {
            auto start = std::chrono::high_resolution_clock::now();
            //loop due to the very short duration of the operation
            for (int i=0; i<REPETITION; i++) {
                copies[i].push_first(n);
            }
            auto stop= std::chrono::high_resolution_clock::now();
            auto duration = duration_cast<std::chrono::nanoseconds>(stop - start);
            return duration.count();
        }
        case 2: {
            auto start = std::chrono::high_resolution_clock::now();
            for (int i=0; i<REPETITION; i++) {
                copies[i].push_back(n);
            }
            auto stop= std::chrono::high_resolution_clock::now();
            auto duration = duration_cast<std::chrono::nanoseconds>(stop - start);
            return duration.count();
        }
        case 3: {
            auto start = std::chrono::high_resolution_clock::now();
            for (int i=0; i<REPETITION; i++) {
                copies[i].push(index, n);
            }
            auto stop= std::chrono::high_resolution_clock::now();
            auto duration = duration_cast<std::chrono::nanoseconds>(stop - start);
            return duration.count();
        }
        case 4: {
            auto start = std::chrono::high_resolution_clock::now();
            for (int i=0; i<REPETITION; i++) {
                copies[i].remove_first();
            }
            auto stop= std::chrono::high_resolution_clock::now();
            auto duration = duration_cast<std::chrono::nanoseconds>(stop - start);
            return duration.count();
        }
        case 5:
            {
                auto start = std::chrono::high_resolution_clock::now();
                for (int i=0; i<REPETITION; i++) {
                    copies[i].remove_last();
                }
                auto stop= std::chrono::high_resolution_clock::now();
                auto duration = duration_cast<std::chrono::nanoseconds>(stop - start);
                return duration.count();
            }

        case 6: {
                auto start = std::chrono::high_resolution_clock::now();
                for (int i=0; i<REPETITION; i++) {
                    copies[i].remove(index);
                }
                auto stop= std::chrono::high_resolution_clock::now();
                auto duration = duration_cast<std::chrono::nanoseconds>(stop - start);
                return duration.count();

            }
        case 7: {
            auto start = std::chrono::high_resolution_clock::now();
            for (int i=0; i<REPETITION; i++) {
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
    //open files with test values and test indexes
    std::ifstream testValuesFile("random_numbers.txt");
    std::ifstream testIndexFile("random_index.txt");
    if (!testValuesFile) {
        std::cerr << "Error: Could not open random_numbers.txt\n";
        return;
    }
    if (!testIndexFile) {
        std::cerr << "Error: Could not open random_index.txt\n";
        return;
    }
    //generate random numbers to file
    for (int i=0;i<12;i++) {
        constexpr int step= 5000;
        const int number = step + i*step;

        unsigned long long result=0;
        for (int j=1; j<4; j++) {

            //read and load data to structures
            std::filesystem::path filePath = std::filesystem::current_path() / (std::to_string(number) + "_" + std::to_string(j) + ".txt");
            std::ifstream RandomNumbersFile(filePath);
            if (!RandomNumbersFile) {
                std::cerr << "Error: Could not open file " << filePath << "\n";
            }
            int element;
            while (RandomNumbersFile >> element) {
                structure.push_back(element);
            }
            RandomNumbersFile.close();

            //load test index and value from files
            int testValue;
            testValuesFile >> testValue;
            int testIndex;
            testIndexFile >> testIndex;

            result += performanceTests(structure, operationChoice, testValue, testIndex);
        }
        toFile(operationChoice, structureName, result/3, std::to_string(number));
        std::cout<<structureName<<" testing completed for "<<std::to_string(number)<<" data set.\n";
    }
}