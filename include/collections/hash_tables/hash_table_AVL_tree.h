#ifndef HASH_TABLE_AVL_TREE_H
#define HASH_TABLE_AVL_TREE_H

#include <string>

struct NodeAVL {
    int key;
    int value;
    int height;
    NodeAVL* left;
    NodeAVL* right;

    explicit NodeAVL(int key, int value)
        : key(key),value(value), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    NodeAVL* root;
    int size;


    static int height(NodeAVL* node);
    static int balance_factor(NodeAVL* node);
    static NodeAVL* left_rotate(NodeAVL* node);
    static NodeAVL* right_rotate(NodeAVL* node);
    NodeAVL* insert(NodeAVL* node, int key, int value);
    NodeAVL* remove(NodeAVL* node, int key);
    static void displayTree(const NodeAVL *node);
    void clear(NodeAVL* node);


public:
    AVLTree();
    ~AVLTree();

    static NodeAVL* copy( NodeAVL* node);
    void copyFrom(const AVLTree& other);
    void insert(const int key, const int value) { root = insert(root, key, value); }
    void remove(const int key) { root = remove(root, key); }
    [[nodiscard]] int getSize() const;
    void display() const;
};

class HashTableAVLTree {

private:
    int size=0;
    int arraySize;
    [[nodiscard]] int getHash(int key) const;
    AVLTree* tab;

public:
    HashTableAVLTree(const HashTableAVLTree& other);
    explicit HashTableAVLTree(int arraySize);
    ~HashTableAVLTree();
    void insert(int key, int value);
    void remove(int key);
    [[nodiscard]] int getSize() const;
    void display() const;
};

#endif //HASH_TABLE_AVL_TREE_H
