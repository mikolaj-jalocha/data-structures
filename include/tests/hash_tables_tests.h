#ifndef HASH_TABLES_TESTS_H
#define HASH_TABLES_TESTS_H
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include "../utils/write_to_file.h"

template<typename Structure>
unsigned long long HashTablesPerformanceTests(Structure& structure, int operation, int n, int key) {
    //create copies of structure to perform reliable test for each one operation
    int REPETITION = 100;
    std::vector<Structure> copies(REPETITION, structure);
    std::string fileName= " ";
    //switch case for all methods for hash tables
    switch (operation) {
        case 1: {
            auto start = std::chrono::high_resolution_clock::now();
            //loop due to the very short duration of the operation
            for (int i=0; i<REPETITION; i++) {
                copies[i].insert(key,n);
            }
            auto stop= std::chrono::high_resolution_clock::now();
            auto duration = duration_cast<std::chrono::nanoseconds>(stop - start);
            return duration.count();
        }
        case 2: {
            auto start = std::chrono::high_resolution_clock::now();
            for (int i=0; i<REPETITION; i++) {
                copies[i].remove(key);
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

template<typename Structure>
void testsForHashTables(Structure& structure, const std::string& structureName, int operationChoice) {
    //open files with test values and test indexes
    std::ifstream testValuesFile("random_numbers.txt");
    std::ifstream testKeyFile("random_index.txt");
    if (!testValuesFile) {
        std::cerr << "Error: Could not open random_numbers.txt\n";
        return;
    }
    if (!testKeyFile) {
        std::cerr << "Error: Could not open random_keys.txt\n";
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
            std::filesystem::path filePathKey = std::filesystem::current_path() / (std::to_string(number) + "_" + std::to_string(j) + "_key.txt");
            std::ifstream RandomNumbersFile(filePath);
            std::ifstream RandomKeysFile(filePathKey);
            if (!RandomNumbersFile) {
                std::cerr << "Error: Could not open file " << filePath << "\n";
            }
            if (!RandomKeysFile) {
                std::cerr << "Error: Could not open file " << filePathKey << "\n";
            }
            int value, key;

            while (RandomNumbersFile >> value && RandomKeysFile >> key) {
                structure.insert(key, value);
            }
            RandomNumbersFile.close();
            result += HashTablesPerformanceTests(structure, operationChoice, value, key);
        }
        toFile(operationChoice, structureName, result/3, std::to_string(number));
        std::cout<<structureName<<" testing completed for "<<std::to_string(number)<<" data set.\n";
    }
}

#endif //HASH_TABLES_TESTS_H
