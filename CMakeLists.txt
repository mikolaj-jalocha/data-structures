cmake_minimum_required(VERSION 3.30)
project(DataStructuresLists)

set(CMAKE_CXX_STANDARD 20)

add_executable(DataStructuresLists main.cpp
        include/singly_linked_list.h
        include/doubly_linked_list.h
        include/array_list.h
)
