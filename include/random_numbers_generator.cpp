//
// Created by Mikolaj Jalocha on 31/03/2025.
//

#include "random_numbers_generator.h"
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <filesystem>

void generateRandomNumbersToFile(int count, const std::string& number) {
    std::string fileName = std::to_string(count) + number + ".txt";

    if (std::filesystem::exists(fileName)) {
        std::cout << "File " << fileName << " already exist. If you want to generate new data, delete mentioned file.\n";
        return;
    }

    std::ofstream outFile(fileName);
    if (!outFile.is_open()) {
        std::cerr << "Can't open the file to write: " << fileName << "\n";
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(INT32_MIN, INT32_MAX);

    std::vector<int> values;
    for (int i = 0; i < count; ++i) {
        int randomNumber = dist(gen);
        values.push_back(randomNumber);
        outFile << randomNumber << "\n";
    }

    outFile.close();
    std::cout << "Generated " << count << " random numbers and saved them to the file: " << fileName << "\n";

    //Generate value for testing methods
    if (!values.empty()) {
        std::uniform_int_distribution<int> int_dist(0, static_cast<int>(values.size() - 1));
        int testValue = values[int_dist(gen)];

        std::string fileNumbersName = "random_numbers.txt";
        std::ofstream outTestFile(fileNumbersName, std::ios::app);
        if (!outTestFile.is_open()) {
            std::cerr << "Can't open the file to write: " << fileNumbersName << "\n";
            return;
        }

        outTestFile << testValue << "\n";
        outTestFile.close();
    }

    //Generate index for testing methods
    std::uniform_int_distribution<int> indexDist(0, count - 1);
    int testIndex = indexDist(gen);
    std::string fileIndexName = "random_index.txt";
    std::ofstream outTestFile(fileIndexName, std::ios::app);
    if (!outTestFile.is_open()) {
        std::cerr << "Can't open the file to write: " << fileIndexName << "\n";
        return;
    }
    outTestFile << testIndex << "\n";
    outTestFile.close();
}