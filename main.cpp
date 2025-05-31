#include <iostream>
#include "include/collections/hash_tables/hash_table_avl_tree.h"

int main() {
    HashTableAVLTree tree(3);
    tree.insert(3, 100);
    tree.insert(6, 200);
    tree.insert(9, 300);
    tree.insert(12, 400);
    tree.insert(5, 200);
    tree.insert(4, 300);
    tree.insert(2, 400);
    tree.display();
    std::cout<<"Size: "<<tree.getSize()<<"\n";

    std::cout<<"\nAfter removing 6,9 and 5\n";
    tree.remove(6);
    tree.remove(9);
    tree.remove(5);
    tree.display();
    std::cout<<"Size:"<<tree.getSize();
    return 0;
}