//
// Created by Mikolaj Jalocha on 31/03/2025.
//

#include "random_numbers_generator.h"
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <filesystem>

int generateRandomNumbersToFile(int count) {
    int testValue=0;
    std::string fileName = std::to_string(count) + ".txt";

    if (std::filesystem::exists(fileName)) {
        std::filesystem::remove(fileName);
    }

    std::ofstream outFile(fileName);
    if (!outFile.is_open()) {
        std::cerr << "Can't open the file to write: " << fileName << "\n";
        return -1;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(INT32_MIN, INT32_MAX);

    std::uniform_int_distribution<int> indexDist(0, count - 1);
    int chosenIndex = indexDist(gen);

    for (int i = 0; i < count; ++i) {
        int randomNumber = dist(gen);
        outFile << randomNumber << "\n";

        if (i == chosenIndex) {
            testValue = randomNumber;
        }
    }

    outFile.close();
    std::cout << "Generated " << count << " random numbers and saved them to the file: " << fileName << "\n";
    return testValue;
}

int generateRandomIndex(int count) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> indexDist(0, count - 1);
    return indexDist(gen);
}