#include "hash_table_AVL_tree.h"
#include<iostream>

AVLTree::AVLTree() : root(nullptr), size(0){ }

void AVLTree::clear(const Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    size--;
    delete node;
}

AVLTree::~AVLTree() {
    clear(root);
}

int AVLTree::height(const Node* node)
{
    return node ? node->height : 0;
}

int AVLTree::balance_factor(const Node* node)
{
    return node ? height(node->left) - height(node->right) : 0;
}

Node* AVLTree::insert(Node* node, int key){
    size++;
    if (node == nullptr)
        return new Node(key);

    if (key < node->key) {
        node->left = insert(node->left, key);
    }
    else if (key > node->key) {
        node -> right = insert(node->right, key);
    } else
        return node;

    node->height = std::max(height(node->left), height(node->right)) +1;
    if (balance_factor(node) > 1 && key < node->left->key) {
        return right_rotate(node);
    }
    if (balance_factor(node) < -1 && key > node->right->key) {
        return left_rotate(node);
    }
    if (balance_factor(node) > 1 && key > node->left->key) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }
    if (balance_factor(node) < -1 && key < node->right->key) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
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
        while (min->left)
            min = min->left;
        node->key = min->key;
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