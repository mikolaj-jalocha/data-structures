//
// Created by Mikolaj Jalocha on 24/05/2025.
//

#ifndef HASHMAP_H
#define HASHMAP_H
#include "../doubly_linked_list.h"


class HashMap {

private:
    int size = 0;
    int arraySize;
    int getHash(int key) const;
    DoublyLinkedList<std::pair<int,int>*>* tab;

public:
    HashMap(const HashMap& other);
    HashMap(int arraySize);
    ~HashMap();
    void insert(int key, int value);
    int find(int key) const;
    int remove(int key);
    int getSize() const;
};

#endif //HASHMAP_H
