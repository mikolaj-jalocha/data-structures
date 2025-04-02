cmake_minimum_required(VERSION 3.30)
project(DataStructuresLists)

set(CMAKE_CXX_STANDARD 20)

add_executable(DataStructuresLists main.cpp
        include/singly_linked_list.h
        include/doubly_linked_list.h
        include/array_list.h
        include/random_numbers_generator.h
        include/random_numbers_generator.cpp
        include/utils/write_to_file.cpp
        include/utils/write_to_file.h
        include/performance_tests.h
        include/perfomance_tests.cpp
)
