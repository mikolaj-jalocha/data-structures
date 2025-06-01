#ifndef HASH_TABLE_AVL_TREE_H
#define HASH_TABLE_AVL_TREE_H

#include <string>

#include "avl_tree.h"


class HashTableAVLTree {

private:
    int size=0;
    int arraySize=5000;
    [[nodiscard]] int getHash(int key) const;
    AVLTree* tab;
    void resize();

public:
    HashTableAVLTree(const HashTableAVLTree& other);
    explicit HashTableAVLTree();
    ~HashTableAVLTree();
    void insert(int key, int value);
    std::pair<int,int> remove(int key);
    [[nodiscard]] int getSize() const;
    void display() const;
};

#endif //HASH_TABLE_AVL_TREE_H
