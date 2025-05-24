//
// Created by Mikolaj Jalocha on 24/05/2025.
//

#include "HashTableLinear.h"

HashTableLinear::HashTableLinear() {
    size = 100;
    count = 0;
    tab = new Element[size];
}

HashTableLinear::~HashTableLinear() {
    delete[] tab;
}

int HashTableLinear::getHash(int key) {
    return key % size;
}

void HashTableLinear::resize() {
    int oldSize = size;
    Element *oldTab = tab;

    size *= 2;
    tab = new Element[size];
    count = 0;

    for (int i = 0; i < oldSize; ++i) {
        if (oldTab[i].state == Element::OCCUPIED) {
            int index = getHash(oldTab[i].key);
            int probes = 0;

            while (probes < size) {
                if (tab[index].state != Element::OCCUPIED) {
                    tab[index] = oldTab[i];
                    tab[index].state = Element::OCCUPIED;
                    count++;
                    break;
                }
                index = (index + 1) % size;
                probes++;
            }
        }
    }

    delete[] oldTab;
}

void HashTableLinear::insert(int key, int value) {
    if ((count + 1) > size * 0.75)
        resize();

    int index = getHash(key);
    int firstDeleted = -1;
    int start = index;

    do {
        if (tab[index].state == Element::OCCUPIED) {
            if (tab[index].key == key) break;
        } else if (tab[index].state == Element::DELETED) {
            if (firstDeleted == -1) firstDeleted = index;
        } else {
            if (firstDeleted != -1) index = firstDeleted;
            break;
        }
        index = (index + 1) % size;
    } while (index != start);

    if (tab[index].state != Element::OCCUPIED) {
        if (firstDeleted != -1) index = firstDeleted;
        count++;
    }

    tab[index].key = key;
    tab[index].value = value;
    tab[index].state = Element::OCCUPIED;
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
