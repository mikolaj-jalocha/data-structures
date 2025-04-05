//
// Created by Mikolaj Jalocha on 31/03/2025.
//

#ifndef RANDOM_NUMBERS_GENERATOR_H
#define RANDOM_NUMBERS_GENERATOR_H

#include <string>

void generateRandomNumbersToFile(int count,const std::string& number);
int getTestValueFromFile(int count, const std::string& number);
int generateRandomIndex(int count);

#endif //RANDOM_NUMBERS_GENERATOR_H
