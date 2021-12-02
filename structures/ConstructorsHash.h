//
// IntegralA
//
// Ian García González
// A01706892
//
// File created on 01/12/21.
//
// Copyright © 2021. All rights reserved.
//
//

#ifndef INTEGRALA_CONSTRUCTORS_HASH_H
#define INTEGRALA_CONSTRUCTORS_HASH_H


#include <string>
#include <iostream>
#include <sstream>

#include "../models/Extra.h"

const int SIZE = 300;

class ConstructorsHash {
private:
    unsigned int (*func)(const std::string);

    unsigned int size;
    unsigned int count;
    std::string *keys[SIZE];
    std::string initialValue;
    Constructor *values[SIZE];

    long indexOf(std::string) const;

public:
    ConstructorsHash(unsigned int, std::string, unsigned int (*)(const std::string));

    ~ConstructorsHash();

    bool full() const;

    bool put(std::string, Constructor);

    bool contains(std::string) const;

    Constructor *get(const std::string &) const;

    std::string toString() const;
};

ConstructorsHash::ConstructorsHash(unsigned int size, std::string initial,
                                   unsigned int (*func)(const std::string)) {
    this->size = SIZE;
    this->initialValue = initial;
    for (unsigned int i = 0; i < SIZE; ++i) {
        this->keys[i] = &initial;
    }
    for (int i = 0; i < SIZE; ++i) {
        this->values[i] = nullptr;
    }
    this->func = func;
    this->count = 0;
}

ConstructorsHash::~ConstructorsHash() {
    for (auto n: keys) {
        delete n;
    }
    for (auto n: values) {
        delete n;
    }
    func = nullptr;
    size = 0;
    count = 0;
}

bool ConstructorsHash::full() const {
    return count > size;
}

long ConstructorsHash::indexOf(const std::string key) const {
    unsigned int i, start;
    start = i = func(key) % size;
    for (int j = 0; j < size; ++j) {
        if (keys[i] == &key) return i;
        i = (start + j * j) % size;
    }
    return -1;
}

bool ConstructorsHash::put(std::string key, Constructor value) {
    unsigned i, start;
    long position;
    position = indexOf(key);
    if (position != -1) {
        values[position] = &value;
        return true;
    }
    start = i = func(key) % size;
    for (int j = 0; j < size; ++j) {
        if (keys[i] == &initialValue) {
            keys[i] = &key;
            values[i] = &value;
        }
        i = (start + j * j) % size;
    }
    return false;
}

bool ConstructorsHash::contains(const std::string key) const {
    return indexOf(key) != -1;
}

Constructor *ConstructorsHash::get(const std::string &key) const {
    long position = indexOf(key);
    if (position != -1) return values[position];
    return nullptr;
}

std::string ConstructorsHash::toString() const {
    std::stringstream aux;
    for (int i = 0; i < size; ++i) {
        if (keys[i] != &initialValue) {
            aux << "(" << i << " ";
            aux << keys[i] << " : " << values[i]->name << ") ";
        }
    }
    return aux.str();
}


#endif //INTEGRALA_CONSTRUCTORS_HASH_H
