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

/**
 * @brief ConstructorsHash class
 * 
 * @tparam Key class
 * @tparam Value class
 */
template<class Key, class Value>
class ConstructorsHash {
private:
    unsigned int (*func)(const Key);

    unsigned int size;
    unsigned int count;

    Key *keys;
    Key initialValue;
    Value *values;

    long indexOf(const Key) const;

public:
    ConstructorsHash(unsigned int, Key, unsigned int (*)(const Key));

    ~ConstructorsHash();

    bool full() const;

    bool put(Key, Value);

    bool contains(Key) const;

    Value get(const Key);

    std::string toString();
};

/**
 * @brief Construct a new Constructors Hash< Key,  Value>:: Constructors Hash object
 * 
 * @tparam Key class
 * @tparam Value class
 * @param size The size of the hash
 * @param initialValue Initial value of the hash
 * @param func Function to hash the keys
 */
template<class Key, class Value>
ConstructorsHash<Key, Value>::ConstructorsHash(unsigned int size, Key initialValue, unsigned int (*func)(const Key)) {
    this->size = size;
    this->keys = new Key[size];
    if (keys == nullptr) std::cout << "[!] No memory." << std::endl;
    this->initialValue = initialValue;
    for (int i = 0; i < size; ++i) {
        this->keys[i] = initialValue;
    }
    values = new Value[size];
    if (values == nullptr) std::cout << "[!] No memory." << std::endl;
    for (int i = 0; i < size; ++i) {
        this->values[i] = -1;
    }
    this->func = func;
    this->count = 0;
}

/**
 * @brief Destroy the Constructors Hash< Key,  Value>:: Constructors Hash object
 * 
 * @tparam Key 
 * @tparam Value 
 */
template<class Key, class Value>
ConstructorsHash<Key, Value>::~ConstructorsHash() {
    delete[] keys;
    delete[] values;
    keys = nullptr;
    values = nullptr;
    func = nullptr;
    size = 0;
    count = 0;
}

/**
 * @brief Check if the hash is full
 * 
 * @tparam Key 
 * @tparam Value 
 * @return true 
 * @return false 
 */
template<class Key, class Value>
bool ConstructorsHash<Key, Value>::full() const {
    return count > size;
}

/**
 * @brief Get the index of the key
 * 
 * @tparam Key 
 * @tparam Value 
 * @param key 
 * @return long 
 */
template<class Key, class Value>
long ConstructorsHash<Key, Value>::indexOf(const Key key) const {
    unsigned int i, start;
    start = i = func(key) % size;
    for (int j = 0; j < size; j++) {
        if (keys[i] == key) return i;
        i = (start + j * j) % size;
    }
    return -1;
}

/**
 * @brief Put the key and value in the hash
 * 
 * @tparam Key 
 * @tparam Value 
 * @param key 
 * @param value 
 * @return true 
 * @return false 
 */
template<class Key, class Value>
bool ConstructorsHash<Key, Value>::put(Key key, Value value) {
    unsigned int i, start;
    long int position;
    position = indexOf(key);
    if (position != -1) {
        values[position] = value;
        return true;
    }
    start = i = func(key) % size;
    for (int j = 0; j < size; ++j) {
        if (keys[i] == initialValue) {
            keys[i] = key;
            values[i] = value;
            return true;
        }
        i = (start + j * j) % size;
    }
    return false;
}

/**
 * @brief Get the value of the key
 * 
 * @tparam Key 
 * @tparam Value 
 * @param key 
 * @return Value 
 */
template<class Key, class Value>
Value ConstructorsHash<Key, Value>::get(const Key key) {
    long int position = indexOf(key);
    if (position != -1) return values[position];
    return 0;
}

/**
 * @brief Check if the key is in the hash
 * 
 * @tparam Key 
 * @tparam Value 
 * @param key 
 * @return true 
 * @return false 
 */
template<class Key, class Value>
bool ConstructorsHash<Key, Value>::contains(Key key) const {
    return indexOf(key) != -1;
}

/**
 * @brief Convert the hash to a string
 * 
 * @tparam Key 
 * @tparam Value 
 * @return std::string 
 */
template<class Key, class Value>
std::string ConstructorsHash<Key, Value>::toString() {
    std::stringstream aux;
    for (int i = 0; i < size; i++) {
        if (keys[i] != initialValue) {
            aux << "(" << i << " ";
            aux << keys[i] << " : " << values[i] << ") ";
        }
    }
    return aux.str();
}

#endif //INTEGRALA_CONSTRUCTORS_HASH_H
