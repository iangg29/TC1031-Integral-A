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

#ifndef INTEGRALA_RACES_LIST_H
#define INTEGRALA_RACES_LIST_H

#include <sstream>
#include <utility>
#include <string>

#include "../models/Extra.h"

class RacesList;

class RacesLink {
private:
    explicit RacesLink(Race);

    RacesLink(Race, RacesLink *);

    Race value;
    RacesLink *next;

    friend class RacesList;
};

RacesLink::RacesLink(Race race) : value(std::move(race)), next(nullptr) {}

RacesLink::RacesLink(Race race, RacesLink *nxt) : value(std::move(race)), next(nxt) {}

class RacesList {
public:
    RacesList();

    ~RacesList();

    void clear();

    void addFirst(Race);

    void insert(const Race &);

    void update(int, Race);

    int search(int) const;

    Race deleteAt(int);

    Race deleteFirst();

    bool isEmpty() const;

    std::string toString() const;

private:
    RacesLink *head;
    int size;
};

RacesList::RacesList() : head(nullptr), size(0) {}

RacesList::~RacesList() {
    clear();
}

void RacesList::clear() {
    RacesLink *p, *q;
    p = head;
    while (p != nullptr) {
        q = p->next;
        delete p;
        p = q;
    }
    head = nullptr;
    size = 0;
}

void RacesList::addFirst(Race race) {
    RacesLink *newLink;
    newLink = new RacesLink(std::move(race));
    newLink->next = head;
    head = newLink;
    size++;
}

void RacesList::insert(const Race &race) {
    RacesLink *newLink, *p;
    newLink = new RacesLink(race);
    if (isEmpty()) {
        addFirst(race);
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

void RacesList::update(int index, Race race) {
    int position;
    RacesLink *p;
    if (index < 0 || index > size) {
        std::cout << "Invalid index" << std::endl;
    }
    position = 0;
    p = head;
    while (position != index) {
        p = p->next;
        position++;
    }
    p->value = std::move(race);
}

int RacesList::search(int id) const {
    int position;
    RacesLink *p;
    if (isEmpty()) return -1;
    p = head;
    position = 0;
    while (p != nullptr) {
        if (p->value.raceId == id) return position;
        p = p->next;
        position++;
    }
    return -1;
}

Race RacesList::deleteAt(int index) {
    RacesLink *p, *q;
    int position;
    if (index < 0 || index >= size) {
        std::cout << "Invalid index" << std::endl;
    }
    if (index == 0) return deleteFirst();
    position = 0;
    p = head;
    q = nullptr;
    while (position != index) {
        q = p;
        p = p->next;
        position++;
    }
    Race race;
    race = p->value;
    q->next = p->next;
    delete p;
    size--;
    return race;
}

Race RacesList::deleteFirst() {
    RacesLink *p;
    if (isEmpty()) {
        std::cout << "List is empty." << std::endl;
    }
    p = head;
    head = p->next;
    Race race = p->value;
    delete p;
    size--;
    return race;
}

bool RacesList::isEmpty() const {
    return head == nullptr;
}

std::string RacesList::toString() const {
    std::stringstream aux;
    RacesLink *p;
    p = head;
    aux << "[";
    while (p != nullptr) {
        aux << p->value.name << "(" << p->value.year << ")";
        if (p->next != nullptr) {
            aux << ", ";
        }
        p = p->next;
    }
    aux << "]";
    return aux.str();
}

#endif //INTEGRALA_RACES_LIST_H
