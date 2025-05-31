cmake_minimum_required(VERSION 3.30)
project(DataStructuresLists)

set(CMAKE_CXX_STANDARD 20)

add_executable(DataStructuresLists main.cpp
        include/collections/singly_linked_list.h
        include/collections/doubly_linked_list.h
        include/collections/array_list.h
        include/utils/random_numbers_generator.h
        include/utils/random_numbers_generator.cpp
        include/utils/write_to_file.cpp
        include/utils/write_to_file.h
        include/performance_tests.h
        include/perfomance_tests.cpp
        include/collections/priority_queues/max_priority_queue_doubly_linked_list.h
        include/collections/priority_queues/max_priority_queue_heap.h
        include/tests/priority_queues_tests.h
        include/tests/lists_and_dynamic_array_tests.h
        include/collections/hash_tables/HashTableLinear.cpp
        include/collections/hash_tables/HashTableLinear.h
        include/collections/hash_tables/HashMap.cpp
        include/collections/hash_tables/HashMap.h
        include/collections/hash_tables/hash_table_AVL_tree.h
        include/collections/hash_tables/hash_table_AVL_tree.cpp
)
