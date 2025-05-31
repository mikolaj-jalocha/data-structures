#include "hash_table_AVL_tree.h"
#include<iostream>

AVLTree::AVLTree() : root(nullptr), size(0){ }

void AVLTree::clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

AVLTree::~AVLTree() {
    clear(root);
    size =0;
}

int AVLTree::height(Node* node)
{
    return node ? node->height : 0;
}

int AVLTree::balance_factor(Node* node)
{
    return node ? height(node->left) - height(node->right) : 0;
}

Node* AVLTree::insert(Node* node, int key, int value){

    if (node == nullptr) {
        size++;
        return new Node(key, value);
    }

    if (key < node->key) {
        node->left = insert(node->left, key, value);
    }
    else if (key > node->key) {
        node -> right = insert(node->right, key, value);
    } else {
        node->value=value;
        return node;
    }
    node->height = std::max(height(node->left), height(node->right)) +1;
    if (balance_factor(node) > 1) {
        if (node->left && key < node->left->key)
            return right_rotate(node);
        if (node->left && key > node->left->key) {
            node->left = left_rotate(node->left);
            return right_rotate(node);
        }
    }
    if (balance_factor(node) < -1) {
        if (node->right && key > node->right->key)
            return left_rotate(node);
        if (node->right && key < node->right->key) {
            node->right = right_rotate(node->right);
            return left_rotate(node);
        }
    }

    return node;
}

Node* AVLTree::left_rotate(Node* node) {
    Node *r_child(node->right);
    Node* rl_grandchild(r_child->left);

    r_child->left = node;
    node->right = rl_grandchild;

    node->height = std::max(height(node->left), height(node->right)) + 1;
    r_child->height = std::max(height(r_child->left), height(r_child->right)) + 1;
    return r_child;
}

Node* AVLTree::right_rotate(Node* node) {
    Node *l_child(node->left);
    Node* lr_grandchild(l_child->right);

    l_child->right = node;
    node->left = lr_grandchild;

    node->height = std::max(height(node->left), height(node->right)) +1 ;
    l_child->height = std::max(height(l_child->left), height(l_child->right))+ 1;
    return l_child;
}

Node* AVLTree::remove(Node* node, const int key) {
    if (node == nullptr)
        return nullptr;

    if (key < node->key) {
        node->left = remove(node->left, key);
    } else if (key > node->key) {
        node->right = remove(node->right, key);
    } else {
        if (node->left == nullptr || node->right == nullptr) {
            size--;
            Node* n = node->left ? node->left : node->right;
            delete node;
            return n;
        }

        const Node* min = node->right;
        while (min->left) {
            min = min->left;
        }
        node->key = min->key;
        node->value = min->value;
        node->right = remove(node->right, min->key);
    }

    node->height = std::max(height(node->left), height(node->right)) + 1;

    if (balance_factor(node) > 1) {
        if (balance_factor(node->left) >= 0)
            return right_rotate(node);
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    
    if (balance_factor(node) < -1) {
        if (balance_factor(node->right) <= 0)
            return left_rotate(node);
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }
    return node;
}
int AVLTree::getSize() const {
    return size;
}
void AVLTree::displayTree(const Node *node) {
    if (node != nullptr) {
        std::cout << "["<<node->key << ": "<<node->value<<"], ";
        displayTree(node->left);
        displayTree(node->right);
    }
}

void AVLTree::display() const {
    displayTree(root);
}

Node* AVLTree::copy( Node* node) {
    if (!node) return nullptr;

    Node* newNode = new Node(node->key, node->value);
    newNode->left = copy(node->left);
    newNode->right = copy(node->right);
    newNode->height = node->height;
    return newNode;
}

void AVLTree::copyFrom(const AVLTree& other) {
    clear(root);
    root = copy(other.root);
    size = other.size;
}


HashTableAVLTree::HashTableAVLTree(int arraySize) {
    this->arraySize = arraySize;
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
}

void HashTableAVLTree::remove(int key) {
    int index = getHash(key);
    tab[index].remove(key);
    size --;
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


