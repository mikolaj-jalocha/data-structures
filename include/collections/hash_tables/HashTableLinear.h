//
// Created by Mikolaj Jalocha on 24/05/2025.
//

#ifndef HASHTABLELINEAR_H
#define HASHTABLELINEAR_H

struct Element {
    int key;
    int value;
    enum { EMPTY, OCCUPIED, DELETED } state;
    Element() : key(0), value(0), state(EMPTY) {}
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
    HashTableLinear(const HashTableLinear& other);
    HashTableLinear& operator=(const HashTableLinear& other);

};

#endif // HASHTABLELINEAR_H
