//
// Created by majam on 02.04.2025.
//

#ifndef PERFORMANCE_TESTS_H
#define PERFORMANCE_TESTS_H
#include <string>

template<typename T>
void performanceTests(T& structure, const std::string& structureName, int operation, int n = 0, int index = 0);
void testsForGeneratedNumbers();
#endif //PERFORMANCE_TESTS_H
