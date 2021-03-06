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

/**
 * @brief RacesLink class.
 * 
 */
class RacesLink {
private:
    explicit RacesLink(Race);

    RacesLink(Race, RacesLink *);

    Race value;
    RacesLink *next;

    friend class RacesList;
};

/**
 * @brief Construct a new Races Link:: Races Link object
 * 
 * @param race Race object.
 */
RacesLink::RacesLink(Race race) : value(std::move(race)), next(nullptr) {}

/**
 * @brief Construct a new Races Link:: Races Link object
 * 
 * @param race Race object.
 * @param nxt Next node.
 */
RacesLink::RacesLink(Race race, RacesLink *nxt) : value(std::move(race)), next(nxt) {}

/**
 * @brief RacesList class.
 */
class RacesList {
public:
    RacesList();

    ~RacesList();

    void clear();

    void addFirst(Race);

    void insert(const Race &);

    void update(int, Race);

    Race *search(unsigned int) const;

    Race deleteAt(int);

    Race deleteFirst();

    bool isEmpty() const;

    std::string toString(int) const;

private:
    RacesLink *head;
    int size;
};

/**
 * @brief Construct a new Races List:: Races List object
 * 
 */
RacesList::RacesList() : head(nullptr), size(0) {}

/**
 * @brief Destroy the Races List:: Races List object
 * 
 */
RacesList::~RacesList() {
    clear();
}

/**
 * @brief Clear the entire list.
 * 
 */
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

/**
 * @brief Add a new Node at the beginning of the list.
 * 
 * @param race
 */
void RacesList::addFirst(Race race) {
    RacesLink *newLink;
    newLink = new RacesLink(std::move(race));
    newLink->next = head;
    head = newLink;
    size++;
}

/**
 * @brief Insert a new Node to the list.
 * 
 * @param race 
 */
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

/**
 * @brief Updates a node within the list.
 * 
 * @param index Índice a actualizar
 * @param race Nuevo valor del nodo
 */
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

/**
 * @brief Search a node within the list.
 * 
 * @param id ID a buscar
 * @return Race* 
 */
Race *RacesList::search(unsigned int id) const {
    RacesLink *p;
    if (isEmpty()) return nullptr;
    p = head;
    while (p != nullptr) {
        if (p->value.raceId == id) return &p->value;
        p = p->next;
    }
    return nullptr;
}

/**
 * @brief Delete a node with certain index.
 * 
 * @param index Index of the node to delete.
 * @return Race 
 */
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

/**
 * @brief Delete the first node of the list.
 * 
 * @return Race 
 */
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

/**
 * @brief Check if the list is empty.
 * 
 * @return true The list is empty.
 * @return false The list is not empty.
 */
bool RacesList::isEmpty() const {
    return head == nullptr;
}

/**
 * @brief Convert the list to a string.
 * 
 * @param count Cuantos nodos a mostrar.
 * @return std::string 
 */
std::string RacesList::toString(int count) const {
    if (count > size) {
        std::cout << "[!] No existen tantas carreras para imprimir. (Max: " << size << ")" << std::endl;
        return "";
    }
    int counter = 1;
    std::stringstream aux;
    RacesLink *p;
    p = head;
    while (p != nullptr && count > 0) {
        aux << counter << ". " << p->value.name << " (" << p->value.year << ")";
        if (p->next != nullptr) {
            aux << std::endl;
        }
        p = p->next;
        count--;
        counter++;
    }
    return aux.str();
}

#endif //INTEGRALA_RACES_LIST_H
