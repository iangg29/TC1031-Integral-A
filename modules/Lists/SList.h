//
// IntegralA
//
// Ian García González
// A01706892
//
// File created on 05/10/21.
//
// Copyright © 2021. All rights reserved.
//
//

#ifndef INTEGRALA_SLIST_H
#define INTEGRALA_SLIST_H

#include "./exceptions/Exception.h"


template<class T>
class SList;

template<class T>
class SListIterator;

template<class T>
class SLink {
private:
    SLink(T);

    SLink(T, SLink<T> *);

    SLink(const SLink<T> &);

    T value;
    SLink<T> *next;

    friend class SList<T>;

    friend class SListIterator<T>;
};

template<class T>
SLink<T>::SLink(T val) :  value(val), next(nullptr) {}

template<class T>
SLink<T>::SLink(T val, SLink<T> *nxt) : value(val), next(nxt) {}

template<class T>
SLink<T>::SLink(const SLink<T> &source) : value(source.value), next(source.next) {}

template<class T>
class SList {
public:
    SList();

    SList(const SList<T> &) throw(OutOfMemory);

    ~SList();

    void addFirst(T) throw(OutOfMemory);

    void add(T) throw(OutOfMemory);

    T getFirst() throw(NoSuchElement);

    T removeFirst() throw(NoSuchElement);

    int length() const;

    T get(int) const;

    bool contains(T) const;

    bool isEmpty() const;

    void clear();

    std::string toString() const;

    void operator=(const SList &);

    void addBefore(SListIterator<T> &, T);

    void addAfter(SListIterator<T> &, T);

    T removeCurrent(SListIterator<T> &);

    bool set(int, T);

    int indexOf(T) const;

    int lastIndexOf(T) const;

    T remove(int);

    bool removeFirstOcurrence(T);

    bool removeLastOcurrence(T);

private:
    SLink<T> *head;

    int size;

    friend class SListIterator<T>;
};

template<class T>
SList<T>::SList() : head(nullptr), size(0) {}

template<class T>
SList<T>::SList(const SList<T> &source) throw(OutOfMemory) {
    SLink<T> *p, *q;
    if (source.isEmpty()) {
        size = 0;
        head = nullptr;
    } else {
        p = source.head;
        head = new SLink<T>(p->value);
        if (head == nullptr) throw OutOfMemory();
        q = head;
        p = p->next;
        while (p != nullptr) {
            q->next = new SLink<T>(p->value);
            if (q->next == nullptr) throw OutOfMemory();
            p = p->next;
            q = q->next;
        }
        size = source.size;
    }
}

template<class T>
SList<T>::~SList() {
    clear();
}

template<class T>
void SList<T>::addFirst(T val) throw(OutOfMemory) {
    SLink<T> *newLink;
    newLink = new SLink<T>(val);
    if (newLink == nullptr) throw OutOfMemory();
    newLink->next = head;
    head = newLink;
    size++;
}

template<class T>
void SList<T>::add(T val) throw(OutOfMemory) {
    SLink<T> *newLink, *p;
    newLink = new SLink<T>(val);
    if (newLink == nullptr) throw OutOfMemory();
    if (isEmpty()) {
        addFirst(val);
        return;
    }
    p = head;
    while (p->next != nullptr) {
        p = p->next;
    }
    newLink->next = nullptr;
    p->next = newLink;
    size++;
}

template<class T>
T SList<T>::getFirst() throw(NoSuchElement) {
    if (isEmpty()) throw NoSuchElement();
    return head->value;
}

template<class T>
T SList<T>::removeFirst() throw(NoSuchElement) {
    T val;
    SLink<T> *p;
    if (isEmpty()) throw NoSuchElement();
    p = head;
    head = p->next;
    val = p->value;
    delete p;
    size--;
    return val;
}

template<class T>
int SList<T>::length() const {
    return size;
}

template<class T>
T SList<T>::get(int index) const {
    int pos;
    SLink<T> *p;

}


#endif //INTEGRALA_SLIST_H
