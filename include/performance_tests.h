//
// Created by majam on 02.04.2025.
//

#ifndef PERFORMANCE_TESTS_H
#define PERFORMANCE_TESTS_H
#include <string>

template<typename T>
unsigned long long performanceTests(T& structure, int operation, int n, int index);

template<typename T>
void testsForGeneratedNumbers(T& structure, const std::string& structureName, int operationChoice);

int runStructureMenu();

#endif //PERFORMANCE_TESTS_H
