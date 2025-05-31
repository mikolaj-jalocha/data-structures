#ifndef HASH_TABLE_AVL_TREE_H
#define HASH_TABLE_AVL_TREE_H

#include <string>

struct Node {
    int key;
    int value;
    int height;
    Node* left;
    Node* right;

    explicit Node(int key, int value)
        : key(key),value(value), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    Node* root;
    int size;


    static int height(Node* node);
    static int balance_factor(Node* node);
    static Node* left_rotate(Node* node);
    static Node* right_rotate(Node* node);
    Node* insert(Node* node, int key, int value);
    Node* remove(Node* node, int key);
    static void displayTree(const Node *node);
    void clear(Node* node);


public:
    AVLTree();
    ~AVLTree();

    static Node* copy( Node* node);
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
