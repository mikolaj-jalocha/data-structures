#ifndef HASH_TABLE_AVL_TREE_H
#define HASH_TABLE_AVL_TREE_H

struct Node {
    int key;
    mutable int height;
    mutable Node* left;
    Node* right;

    explicit Node(int key)
        : key(key), height(1), left(nullptr), right(nullptr) {}
};

class AVLTree {
private:
    Node* root;
    int size;


    static int height(const Node* node);
    static int balance_factor(const Node* node);
    static Node* left_rotate(Node* node);
    static Node* right_rotate(Node* node);
    Node* insert(Node* node, int key);
    Node* remove(Node* node, int key);

    void clear(const Node* node);


public:
    AVLTree();
    ~AVLTree();

    void insert(const int key) { root = insert(root, key); }
    void remove(const int key) { root = remove(root, key); }

};


#endif //HASH_TABLE_AVL_TREE_H
