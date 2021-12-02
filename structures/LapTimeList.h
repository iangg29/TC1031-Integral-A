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

/**
 * @brief Doubly Link class.
 * 
 */
class Link {
private:
    explicit Link(LapTime);

    Link(LapTime, Link *, Link *);

    LapTime value;
    Link *previous;
    Link *next;

    friend class LapTimeList;
};

/**
 * @brief Construct a new Link:: Link object
 * 
 * @param lapTime 
 */
Link::Link(LapTime lapTime) : value(std::move(lapTime)), previous(nullptr), next(nullptr) {}

/**
 * @brief Construct a new Link:: Link object
 * 
 * @param lapTime 
 * @param prev 
 * @param nxt 
 */
Link::Link(LapTime lapTime, Link *prev, Link *nxt) : value(std::move(lapTime)), previous(prev), next(nxt) {}

/**
 * @brief LapTimeList class.
 * 
 */
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

private:
    Link *head;
    Link *tail;
    int size;

};

/**
 * @brief Construct a new Lap Time List:: Lap Time List object
 * 
 */
LapTimeList::LapTimeList() : head(nullptr), tail(nullptr), size(0) {}

/**
 * @brief Destroy the Lap Time List:: Lap Time List object
 * 
 */
LapTimeList::~LapTimeList() {
    clear();
}

/**
 * @brief Clear the list
 * 
 */
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

/**
 * @brief Insert a new Lap Time
 * 
 * @param lapTime 
 */
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

/**
 * @brief Update a lap time in a certain index.
 * 
 * @param index Index of the lap time to update.
 * @param lapTime 
 */
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

/**
 * @brief Check if the list is empty.
 * 
 * @return true The list is empty.
 * @return false The list is not empty.
 */
bool LapTimeList::isEmpty() const {
    return (head == nullptr && tail == nullptr);
}

/**
 * @brief Convert the list to a string in forward order.
 * 
 * @return std::string 
 */
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

/**
 * @brief Convert the list to a string in backward order.
 * 
 * @return std::string 
 */
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

/**
 * @brief Search a lap time in the list.
 * 
 * @param raceId 
 * @return int 
 */
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

/**
 * @brief Delete the first lap time.
 * 
 * @return LapTime 
 */
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

/**
 * @brief Delete a lap time in a certain index.
 * 
 * @param index Index of the lap time to delete.
 * @return LapTime 
 */
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

/**
 * @brief Convert the list to a vector.
 * 
 * @return std::vector<LapTime> 
 */
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


#endif //INTEGRALA_LAP_TIME_LIST_H
