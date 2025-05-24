//
// Created by Mikolaj Jalocha on 24/05/2025.
//

#ifndef HASHTABLELINEAR_H
#define HASHTABLELINEAR_H

struct Element {
    int key;
    int value;

    enum { EMPTY, OCCUPIED, DELETED } state = EMPTY;
};

class HashTableLinear {
private:
    int size;
    int count;
    Element *tab;

    int getHash(int key);

    void resize();

public:
    HashTableLinear();

    ~HashTableLinear();

    void insert(int key, int value);

    int find(int key);

    bool remove(int key);
};

#endif // HASHTABLELINEAR_H
