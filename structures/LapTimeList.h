//
// IntegralA
//
// Ian García González
// A01706892
//
// File created on 25/11/21.
//
// Copyright © 2021. All rights reserved.
//
//

#ifndef INTEGRALA_LAP_TIME_LIST_H
#define INTEGRALA_LAP_TIME_LIST_H

#include <utility>

#include "../models/Extra.h"

class LapTimeList;

class Link {
private:
    explicit Link(LapTime);

    Link(LapTime, Link *, Link *);

    LapTime value;
    Link *previous;
    Link *next;

    friend class LapTimeList;
};

Link::Link(LapTime lapTime) : value(std::move(lapTime)), previous(nullptr), next(nullptr) {}

Link::Link(LapTime lapTime, Link *prev, Link *nxt) : value(std::move(lapTime)), previous(prev), next(nxt) {}

class LapTimeList {
public:
    LapTimeList();

    ~LapTimeList();

    void clear();

    void insert(LapTime);

    void update(int, LapTime);

    bool isEmpty() const;

    std::string toStringForward() const;

    std::string toStringBackward() const;

    int search(int) const;

    LapTime deleteFirst();

    LapTime deleteAt(int);

    std::vector<LapTime> toVec() const;

    int getSize() const;

private:
    Link *head;
    Link *tail;
    int size;

};

LapTimeList::LapTimeList() : head(nullptr), tail(nullptr), size(0) {}

LapTimeList::~LapTimeList() {
    clear();
}

void LapTimeList::clear() {
    Link *p, *q;
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

void LapTimeList::insert(LapTime lapTime) {
    Link *newNode;
    newNode = new Link(std::move(lapTime));
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

void LapTimeList::update(int index, LapTime lapTime) {
    int position;
    Link *p;
    if (index < 0 || index >= size) {
        std::cout << "Invalid index." << std::endl;
    }
    position = 0;
    p = head;
    while (position != index) {
        p = p->next;
        position++;
    }
    p->value = std::move(lapTime);
}

bool LapTimeList::isEmpty() const {
    return (head == nullptr && tail == nullptr);
}

std::string LapTimeList::toStringForward() const {
    std::stringstream aux;
    Link *p;
    p = head;
    aux << "[";
    while (p != nullptr) {
        aux << p->value.time;
        if (p->next != nullptr) {
            aux << ", ";
        }
        p = p->next;
    }
    aux << "]";
    return aux.str();
}

std::string LapTimeList::toStringBackward() const {
    std::stringstream aux;
    Link *p;
    p = tail;
    aux << "[";
    while (p != nullptr) {
        aux << p->value.time;
        if (p->previous != nullptr) {
            aux << ", ";
        }
        p = p->previous;
    }
    aux << "]";
    return aux.str();
}

int LapTimeList::search(int raceId) const {
    int position;
    Link *p;
    p = head;
    position = 0;
    while (p != nullptr) {
        if (p->value.raceId == raceId) return position; // TODO: Maybe print record.
        p = p->next;
        position++;
    }
    return -1;
}

LapTime LapTimeList::deleteFirst() {
    LapTime lapTime;
    Link *p;
    if (isEmpty()) {
        std::cout << "List empty." << std::endl;
    }
    p = head;
    lapTime = p->value;
    if (head == tail) {
        head = nullptr;
        tail = nullptr;
    } else {
        head = p->next;
        p->next->previous = nullptr;
    }
    delete p;
    size--;
    return lapTime;
}

LapTime LapTimeList::deleteAt(int index) {
    LapTime lapTime;
    Link *p;
    int position;
    if (index < 0 || index >= size) {
        std::cout << "Invalid index" << std::endl;
    }
    if (index == 0) return deleteFirst();
    p = head;
    position = 0;
    while (position != index) {
        p = p->next;
        position++;
    }
    lapTime = p->value;
    p->previous->next = p->next;
    if (p->next != nullptr) {
        p->next->previous = p->previous;
    }
    delete p;
    size--;
    return lapTime;
}

std::vector<LapTime> LapTimeList::toVec() const {
    std::vector<LapTime> sortedDlist;
    Link *p;
    p = head;
    while (p != nullptr) {
        sortedDlist.push_back(p->value);
        p = p->next;
    }
    return sortedDlist;
}

int LapTimeList::getSize() const {
    return size;
}


#endif //INTEGRALA_LAP_TIME_LIST_H
