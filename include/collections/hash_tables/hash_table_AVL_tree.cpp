#include "hash_table_AVL_tree.h"
#include<iostream>

#include "avl_tree.h"

HashTableAVLTree::HashTableAVLTree() {
    tab = new AVLTree[this->arraySize];
}
HashTableAVLTree::~HashTableAVLTree() {
    delete [] tab;
}
int HashTableAVLTree::getHash(int key) const {
    return key % arraySize;
}

void HashTableAVLTree::insert(int key, int value) {
    int index = getHash(key);
    tab[index].insert(key, value);
    size++;
    float loadFactor = static_cast<float>(size) / arraySize;
    if (loadFactor >= 2.5) {
        resize();
    }
}

std::pair<int,int> HashTableAVLTree::remove(int key) {
    int index = getHash(key);
    size --;
    return tab[index].remove(key);
}

int HashTableAVLTree::getSize() const {
    return size;
}

HashTableAVLTree::HashTableAVLTree(const HashTableAVLTree& other)
    : size(other.size), arraySize(other.arraySize) {

    tab = new AVLTree[arraySize];
    for (int i = 0; i < arraySize; ++i) {
        tab[i].copyFrom(other.tab[i]);
    }
}

void HashTableAVLTree::display() const {
    for (int i = 0; i < arraySize; ++i) {
        std::cout << "Bucket " << i << ": ";
        tab[i].display();
        std::cout << std::endl;
    }
}
void HashTableAVLTree::resize() {
    arraySize*=2;
    AVLTree *newTab = new AVLTree[arraySize];
    for (int i = 0; i < arraySize/2; i++) {
        while (tab[i].getSize() != 0) {
            std::pair<int,int> myPair = tab[i].remove(tab[i].getRootKey());
            int index = this->getHash(myPair.first);
            newTab[index].insert(myPair.first,myPair.second);
        }
    }
    delete [] tab;
    tab = newTab;
}



