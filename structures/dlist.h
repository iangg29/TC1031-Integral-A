//
// IntegralA
//
// Ian García González
// A01706892
//
// File created on 22/11/21.
//
// Copyright © 2021. All rights reserved.
//
//

#ifndef INTEGRALA_DLIST_H
#define INTEGRALA_DLIST_H

#include <iostream>
#include <sstream>
#include <string>

template<class T>
class DList;

template<class T>
class DLink {
private:
    explicit DLink(T);

    DLink(T, DLink<T> *, DLink<T> *);

    T value;
    DLink<T> *previous;
    DLink<T> *next;

    friend class DList<T>;
};

template<class T>
DLink<T>::DLink(T value) {
    this->value = value;
    this->previous = nullptr;
    this->next = nullptr;
}

template<class T>
DLink<T>::DLink(T value, DLink<T> *previous, DLink<T> *next) {
    this->value = value;
    this->previous = previous;
    this->next = next;
}

template<class T>
class DList {
public:
    DList();

    ~DList();

    void clear();

    void insert(T);

    void update(int, T);

    bool isEmpty() const;

    std::string toStringForward() const;

    std::string toStringBackwards() const;

    int search(T) const;

    T deleteFirst();

    T deleteAt(int);

private:
    DLink<T> *head;
    DLink<T> *tail;
    int size;
};

template<class T>
DList<T>::DList() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template<class T>
DList<T>::~DList() {
    clear();
}

template<class T>
void DList<T>::clear() {
    DLink<T> *p, *q;
    p = head;
    while (p != nullptr) {
        q = p->next;
        delete p;
        p = q;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template<class T>
void DList<T>::insert(T value) {
    DLink<T> *newNode;
    newNode = new DLink<T>(value);
    if (isEmpty()) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->previous = tail;
        tail = newNode;
    }
    size++;
}

template<class T>
void DList<T>::update(int index, T value) {
    int position;
    DLink<T> *p;
    if (index < 0 || index >= size) {
        std::cout << "[ERROR] Index inválido." << std::endl;
        return;
    }
    position = 0;
    p = head;
    while (position != index) {
        p = p->next;
        position++;
    }
    p->value = value;
}

template<class T>
bool DList<T>::isEmpty() const {
    return (head == nullptr && tail == nullptr);
}

template<class T>
std::string DList<T>::toStringForward() const {
    std::stringstream aux;
    DLink<T> *p;

    p = head;
    aux << "[";
    while (p != 0) {
        aux << p->value;
        if (p->next != 0) {
            aux << ", ";
        }
        p = p->next;
    }
    aux << "]";
    return aux.str();
}

template<class T>
std::string DList<T>::toStringBackwards() const {
    std::stringstream aux;
    DLink<T> *p;

    p = tail;
    aux << "[";
    while (p != 0) {
        aux << p->value;
        if (p->previous != 0) {
            aux << ", ";
        }
        p = p->previous;
    }
    aux << "]";
    return aux.str();
}

template<class T>
int DList<T>::search(T value) const {
    int position;
    DLink<T> *p;
    p = head;
    position = 0;
    while (p != nullptr) {
        if (p->value == value) return position;
        p = p->next;
        position++;
    }
    return -1;
}

template<class T>
T DList<T>::deleteFirst() {
    T value;
    DLink<T> *p;
    if (isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }
    p = head;
    value = p->value;
    if (head == tail) {
        head = nullptr;
        tail = nullptr;
    } else {
        head = p->next;
        p->next->previous = nullptr;
    }
    delete p;
    size--;
    return value;
}

template<class T>
T DList<T>::deleteAt(int index) {
    T value;
    DLink<T> *p;
    int position;
    if (index < 0 || index >= size) {
        std::cout << "Invalid index." << std::endl;
        return;
    }
    if (index == 0) return deleteFirst();
    p = head;
    position = 0;
    while (position != index) {
        p = p->next;
        position++;
    }
    value = p->value;
    p->previous->next = p->next;
    if (p->next != nullptr) {
        p->next->previous = p->previous;
    }
    delete p;
    size--;
    return value;
}

#endif //INTEGRALA_DLIST_H
