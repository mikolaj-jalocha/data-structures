//
// Created by Mikolaj Jalocha on 31/03/2025.
//

#include "random_numbers_generator.h"
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <filesystem>

void generateRandomNumbersToFile(int count) {

    std::string fileName = std::to_string(count) + ".txt";

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

    for (int i = 0; i < count; ++i) {
        int randomNumber = dist(gen);
        outFile << randomNumber << "\n";
    }

    outFile.close();
    std::cout << "Generated  " << count << " random numbers and saved them to the file: " << fileName << "\n";
}
