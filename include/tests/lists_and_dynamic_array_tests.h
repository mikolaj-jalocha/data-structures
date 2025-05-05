#ifndef LISTS_AND_DYNAMIC_ARRAY_TESTS_H
#define LISTS_AND_DYNAMIC_ARRAY_TESTS_H
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "../utils/write_to_file.h"

template<typename T>
unsigned long long ListPerformanceTests(T& structure, int operation, int n, int index) {
    //create copies of structure to perform reliable test for each one operation
    int REPETITION = 100;
    std::vector<T> copies(REPETITION, structure);
    std::string fileName= " ";
    //switch case for all methods for lists
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
}

template<typename T>
void testsForLists(T& structure, const std::string& structureName, int operationChoice) {
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

            //load test index and value from files
            int testValue;
            testValuesFile >> testValue;
            int testIndex;
            testIndexFile >> testIndex;

            while (RandomNumbersFile >> element) {
                structure.push_back(element);
            }
            RandomNumbersFile.close();
            result += ListPerformanceTests(structure, operationChoice, testValue, testIndex);
        }
        toFile(operationChoice, structureName, result/3, std::to_string(number));
        std::cout<<structureName<<" testing completed for "<<std::to_string(number)<<" data set.\n";
    }
}

#endif //LISTS_AND_DYNAMIC_ARRAY_TESTS_H
