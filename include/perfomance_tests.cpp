#include "performance_tests.h"
#include "collections/singly_linked_list.h"
#include "collections/doubly_linked_list.h"
#include "collections/array_list.h"
#include "collections/hash_tables/HashMap.h"
#include "collections/hash_tables/HashTableLinear.h"
#include "collections/hash_tables/hash_table_AVL_tree.h"
#include "collections/priority_queues/max_priority_queue_doubly_linked_list.h"
#include "collections/priority_queues/max_priority_queue_heap.h"
#include "utils/random_numbers_generator.h"
#include "tests/lists_and_dynamic_array_tests.h"
#include "tests/priority_queues_tests.h"
#include "tests/hash_tables_tests.h"

int runStructureMenu() {

    //generate files with data sets
    for (int i=0; i<12; i++) {
        constexpr int step= 5000;
        const int number = step + i*step;
        generateRandomNumbersToFile(number, "_1");
        generateRandomNumbersToFile(number, "_2");
        generateRandomNumbersToFile(number, "_3");
    }

    while (true) {
        int topicChoice;
        int structureChoice;
        int operationChoice;
        std::cout<<"Choose:\n1-Lists and dynamic array\n2-Priority queues\n3-Hash tables\n0-Exit\n";
        std::cin >> topicChoice;
        if (topicChoice==0) return 0;
        if (topicChoice==1) {
            std::cout<<"Choose the structure:\n1-Array list\n2-Singly linked list\n3-Doubly linked list\n4-All tests at once\n";
            std::cin >> structureChoice;
            if (structureChoice != 4) {
                std::cout << "Choose the operation:\n1 - Push first\n2 - Push last\n3 - Push at index\n4 - Remove first\n5 - Remove last\n6 - Remove at index\n7 - Search\n";
                std::cin>>operationChoice;
            }
        } else if (topicChoice==2) {
            std::cout<<"Choose the structure:\n1-Max priority queue heap\n2-Max priority queue doubly linked list\n3-All tests at once\n";
            std::cin >> structureChoice;
            //adjustment to one switch case
            structureChoice +=4;
            if (structureChoice != 7) {
                std::cout << "Choose the operation:\n1 - Insert\n2 - Extract max\n3 - Peek\n4 - Modify key\n5 - Return size\n";
                std::cin>>operationChoice;
            }
        }
        else if (topicChoice==3) {
            std::cout<<"Choose the structure:\n1-Hash table linear\n2-Hash table with doubly linked list\n3-Hash table with AVL tree\n4-All tests at once\n";
            std::cin >> structureChoice;
            //adjustment to one switch case
            structureChoice +=7;
            if (structureChoice != 11) {
                std::cout << "Choose the operation:\n1 - Insert\n2 - Remove\n";
                std::cin>>operationChoice;
            }
        }

        switch (structureChoice) {
            case 1: {
                ArrayList<int> arrayList;
                testsForLists(arrayList, "Array List", operationChoice);
                break;
            }
            case 2: {
                SinglyLinkedList<int> SinglyLinkedList;
                testsForLists(SinglyLinkedList, "Singly Linked List", operationChoice);
                break;
            }
            case 3: {
                DoublyLinkedList<int> DoublyLinkedList;
                testsForLists(DoublyLinkedList, "Doubly Linked List", operationChoice);
                break;
            }
            case 4: {
                for (int i=1; i<=7; i++) {
                    ArrayList<int> arrayList;
                    testsForLists(arrayList, "Array List", i);
                    SinglyLinkedList<int> SinglyLinkedList;
                    testsForLists(SinglyLinkedList, "Singly Linked List", i);
                    DoublyLinkedList<int> DoublyLinkedList;
                    testsForLists(DoublyLinkedList, "Doubly Linked List", i);
                }
                break;
            }
            case 5: {
                MaxPriorityQueueHeap<int> PQueueHeap;
                testsForQueues(PQueueHeap, "Max priority queue heap", operationChoice);
                break;
            }
            case 6: {
                MaxPriorityQueueDoublyLinkedList<int> PQueueDoublyLinkedList;
                testsForQueues(PQueueDoublyLinkedList, "Max priority queue doubly linked list", operationChoice);
                break;
            }
            case 7: {
                for (int i=1; i<=5; i++) {
                    MaxPriorityQueueHeap<int> PQueueHeap;
                    testsForQueues(PQueueHeap, "Max priority queue heap", i);
                    MaxPriorityQueueDoublyLinkedList<int> PQueueDoublyLinkedList;
                    testsForQueues(PQueueDoublyLinkedList, "Max priority queue doubly linked list", i);
                }
                break;
            }
            case 8: {
                HashTableLinear hashTableLinear;
                testsForHashTables(hashTableLinear, "Hash table linear", operationChoice);
                break;
            }
            case 9: {
                HashMap hashTableDoublyLinkedList(1000);
                testsForHashTables(hashTableDoublyLinkedList, "Hash table with doubly linked list", operationChoice);
                break;
            }
            case 10: {
                HashTableAVLTree hashTableAVLTree(1000);
                testsForHashTables(hashTableAVLTree, "Hash table with AVL tree", operationChoice);
                break;
            }
            case 11: {
                for (int i=1; i<=2; i++) {
                    HashTableLinear hashTableLinear;
                    testsForHashTables(hashTableLinear, "Hash table linear", i);
                    HashMap hashTableDoublyLinkedList(1000);
                    testsForHashTables(hashTableDoublyLinkedList, "Hash table with doubly linked list", i);
                    HashTableAVLTree hashTableAVLTree(1000);
                    testsForHashTables(hashTableAVLTree, "Hash table with AVL tree", i);
                }
                break;
            }
            default:
                std::cout << "Wrong choice\n";
                break;
        }
    }
}