#ifndef PRIORITY_QUEUES_TESTS_H
#define PRIORITY_QUEUES_TESTS_H
#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "../utils/write_to_file.h"
#include <fstream>

template<typename T>
unsigned long long QueuePerformanceTests(T& structure, int operation, int n, int priority) {
    //create copies of structure to perform reliable test for each one operation
    int REPETITION = 100;
    std::vector<T> copies(REPETITION, structure);
    std::string fileName= " ";
    switch (operation) {
            case 1: {
                auto start = std::chrono::high_resolution_clock::now();
                //loop due to the very short duration of the operation
                for (int i=0; i<REPETITION; i++) {
                    copies[i].insert(n,priority);
                }
                auto stop= std::chrono::high_resolution_clock::now();
                auto duration = duration_cast<std::chrono::nanoseconds>(stop - start);
                return duration.count();
            }
            case 2: {
                auto start = std::chrono::high_resolution_clock::now();
                for (int i=0; i<REPETITION; i++) {
                    copies[i].extract_max();
                }
                auto stop= std::chrono::high_resolution_clock::now();
                auto duration = duration_cast<std::chrono::nanoseconds>(stop - start);
                return duration.count();
            }
            case 3: {
                auto start = std::chrono::high_resolution_clock::now();
                for (int i=0; i<REPETITION; i++) {
                    copies[i].peek();
                }
                auto stop= std::chrono::high_resolution_clock::now();
                auto duration = duration_cast<std::chrono::nanoseconds>(stop - start);
                return duration.count();
            }
            case 4: {
                auto start = std::chrono::high_resolution_clock::now();
                for (int i=0; i<REPETITION; i++) {
                    copies[i].modify_key(n,priority);
                }
                auto stop= std::chrono::high_resolution_clock::now();
                auto duration = duration_cast<std::chrono::nanoseconds>(stop - start);
                return duration.count();
            }
            case 5: {
                auto start = std::chrono::high_resolution_clock::now();
                for (int i=0; i<REPETITION; i++) {
                    copies[i].return_size();
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
void testsForQueues(T& structure, const std::string& structureName, int operationChoice){
    //open files with test values and test indexes
    std::ifstream testValuesFile("random_numbers.txt");
    std::ifstream testPFile("random_priority.txt");
    if (!testValuesFile) {
        std::cerr << "Error: Could not open random_numbers.txt\n";
        return;
    }
    if (!testPFile) {
        std::cerr << "Error: Could not open random_priority.txt\n";
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
            int testPriority;
            testPFile >> testPriority;

            T freshStructure;
            while (RandomNumbersFile >> element) {
                freshStructure.insert(element, testPriority);
            }
            result += QueuePerformanceTests(structure, operationChoice, testValue,  testPriority);
        }
        toFile(operationChoice, structureName, result/3, std::to_string(number));
        std::cout<<structureName<<" testing completed for "<<std::to_string(number)<<" data set.\n";
    }
}
#endif //PRIORITY_QUEUES_TESTS_H
