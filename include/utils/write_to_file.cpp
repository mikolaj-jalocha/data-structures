//
// Created by majam on 02.04.2025.
//
#include "write_to_file.h"

#include <fstream>
#include <iostream>

void toFile(const std::string& fileName, const std::string& sectionName, long long duration, bool newSet) {
    std::ofstream file(fileName, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return;
    }
    if (!newSet) {
        file << sectionName << ":\n" << duration << "\n";
    }else {
        file << "\nTime in nanoseconds for "<<sectionName<<" data set.\n\n";
    }
    file.close();
}