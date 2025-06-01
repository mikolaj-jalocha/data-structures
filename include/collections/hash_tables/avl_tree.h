//
// Created by Mikolaj Jalocha on 01/06/2025.
//

#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <utility>

struct NodeAVL {
    int key;
    int value;
    int height;
    NodeAVL *left;
    NodeAVL *right;

    explicit NodeAVL(int key, int value)
        : key(key), value(value), height(1), left(nullptr), right(nullptr) {
    }
};

class AVLTree {
private:
    NodeAVL *root;
    int size;

    static int height(NodeAVL *node);

    static int balance_factor(NodeAVL *node);

    static NodeAVL *left_rotate(NodeAVL *node);

    static NodeAVL *right_rotate(NodeAVL *node);

    NodeAVL *insert(NodeAVL *node, int key, int value);

    NodeAVL *remove(NodeAVL *node, int key);

    static void displayTree(const NodeAVL *node);

    void clear(NodeAVL *node);

public:
    AVLTree();

    ~AVLTree();

    static NodeAVL *copy(NodeAVL *node);

    void copyFrom(const AVLTree &other);

    int getRootKey() const {return root->key;}

    void insert(const int key, const int value) { root = insert(root, key, value); }

    std::pair<int,int> remove(const int key) {
        std::pair<int,int> myPair = std::pair(root->key, root->value);
        root = remove(root, key);
        return myPair;
    }

    [[nodiscard]] int getSize() const;

    void display() const;
};


#endif //AVL_TREE_H
