//
// Created by Mikolaj Jalocha on 24/05/2025.
//

#include "HashMap.h"


HashMap::HashMap() {
    tab = new DoublyLinkedList<std::pair<int, int> *>[arraySize];
}
HashMap::~HashMap() {
    delete [] tab;
}
int HashMap::getHash(int key) const {
    return key % arraySize;
}

void HashMap::insert(int key, int value) {
    auto* myPair = new std::pair<int,int>(key,value);
    int index = this->getHash(key);
    tab[index].push_first(myPair);
    size++;
    float loadFactor = static_cast<float>(size) / arraySize;
    if (loadFactor >= 0.75f) {
        resize();
    }
}

int HashMap::remove(int key) {
    int index = this->getHash(key);
    for (int i = 0; i < tab[index].getSize(); i++) {
        auto* myPair = tab[index].get(i);
        if (myPair->first == key) {
            size--;
            tab[index].remove(i);
            int returnValue =  myPair->second;
            delete myPair;
            return returnValue;
        }
    }
    throw std::out_of_range("Key not found in map");
}
int HashMap::find(int key) const {
    int index = this->getHash(key);
    for (int i = 0; i < tab[index].getSize(); i++) {
        auto* myPair = tab[index].get(i);
        if (myPair->first == key) {
            return myPair->second;
        }
    }
    throw std::out_of_range("Key not found in map");
}
int HashMap::getSize() const {
    return size;
}
void HashMap::resize() {
    arraySize *= 2;
    DoublyLinkedList<std::pair<int,int>*>* newTab = new DoublyLinkedList<std::pair<int, int> *>[this->arraySize];

    for (int i = 0; i < arraySize/2; i++) {
        while (!tab[i].isEmpty()) {
            auto* myPair = tab[i].remove_first();
            int index = this->getHash(myPair->first);
            newTab[index].push_first(myPair);
        }
    }
    delete [] tab;
    tab = newTab;
}


HashMap::HashMap(const HashMap& other) {
    this->arraySize = other.arraySize;
    this->size = other.size;
    tab = new DoublyLinkedList<std::pair<int, int>*>[this->arraySize];

    for (int i = 0; i < arraySize; i++) {
        for (int j = 0; j < other.tab[i].getSize(); j++) {
            auto* originalPair = other.tab[i].get(j);
            auto* copiedPair = new std::pair<int, int>(*originalPair);
            tab[i].push_first(copiedPair);
        }
    }
}