//
// Created by Mikolaj Jalocha on 24/05/2025.
//

#include "HashTableLinear.h"

HashTableLinear::HashTableLinear() {
    size = 100;
    count = 0;
    tab = new Element[size];
    for(int i=0; i<size; i++) tab[i].state = Element::EMPTY;
}

HashTableLinear::~HashTableLinear() {
    delete[] tab;
}

HashTableLinear::HashTableLinear(const HashTableLinear& other) {
    size = other.size;
    count = other.count;
    tab = new Element[size];

    for (int i = 0; i < size; ++i) {
        tab[i] = other.tab[i];
    }
}

HashTableLinear& HashTableLinear::operator=(const HashTableLinear& other) {
    if (this == &other)
        return *this;
    delete[] tab;

    size = other.size;
    count = other.count;
    tab = new Element[size];

    for (int i = 0; i < size; ++i) {
        tab[i] = other.tab[i];
    }
    return *this;
}

int HashTableLinear::getHash(int key) {
    return key % size;
}
void HashTableLinear::resize() {
    int oldSize = size;
    Element* oldTab = tab;
    if (oldTab == nullptr) return;

    size *= 2;
    tab = new Element[size];
    count = 0;

    for (int i = 0; i < oldSize; ++i) {
        if (oldTab[i].state == Element::OCCUPIED) {
            int index = getHash(oldTab[i].key);
            int probes = 0;

            while (probes < size) {
                if (tab[index].state != Element::OCCUPIED) {
                    tab[index] = oldTab[i]; // state already OCCUPIED
                    count++;
                    break;
                }
                index = (index + 1) % size;
                probes++;
            }
        }
    }

    delete[] oldTab;
    oldTab = nullptr;
}

void HashTableLinear::insert(int key, int value) {
    if ((count + 1) > size * 0.75)
        resize();

    int index = getHash(key);
    int firstDeleted = -1;
    int probes = 0;

    while (probes < size) {
        if (tab[index].state == Element::OCCUPIED) {
            if (tab[index].key == key) {
                tab[index].value = value; // update only
                return;
            }
        } else if (tab[index].state == Element::DELETED) {
            if (firstDeleted == -1)
                firstDeleted = index;
        } else { // EMPTY
            if (firstDeleted != -1)
                index = firstDeleted;
            break;
        }
        index = (index + 1) % size;
        probes++;
    }

    tab[index].key = key;
    tab[index].value = value;
    tab[index].state = Element::OCCUPIED;
    count++;
}

int HashTableLinear::find(int key) {
    int index = getHash(key);
    int start = index;
    do {
        if (tab[index].state == Element::OCCUPIED && tab[index].key == key)
            return tab[index].value;
        if (tab[index].state == Element::EMPTY)
            break;
        index = (index + 1) % size;
    } while (index != start);
    return -1;
}

bool HashTableLinear::remove(int key) {
    int index = getHash(key);
    int start = index;
    do {
        if (tab[index].state == Element::OCCUPIED && tab[index].key == key) {
            tab[index].state = Element::DELETED;
            count--;
            return true;
        }
        if (tab[index].state == Element::EMPTY)
            break;
        index = (index + 1) % size;
    } while (index != start);
    return false;
}
