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

#ifndef INTEGRALA_DRIVERS_BST_H
#define INTEGRALA_DRIVERS_BST_H

#include <sstream>

#include "../models/Extra.h"

class DriversBST;

class BSTNode {
private:
    Driver value;
    BSTNode *left, *right;
public:
    explicit BSTNode(Driver);

    BSTNode(Driver, BSTNode *, BSTNode *);

    void add(const Driver &);

    Driver *find(unsigned int);

    void preorder(std::stringstream &) const;

    void inorder(std::stringstream &, int &, int &) const;

    void postorder(std::stringstream &) const;

    void printlevel(std::stringstream &, int) const;

    void levelorder(std::stringstream &) const;

    int height() const;

    bool ancestors(const Driver &, std::stringstream &);

    int whatLevelAmI(const Driver &);

    friend class DriversBST;
};

BSTNode::BSTNode(Driver driver) : value(std::move(driver)), left(nullptr), right(nullptr) {}

BSTNode::BSTNode(Driver driver, BSTNode *le, BSTNode *ri) : value(std::move(driver)), left(le), right(ri) {}

void BSTNode::add(const Driver &driver) {
    if (driver.driverId < value.driverId) {
        if (left != nullptr) {
            left->add(driver);
        } else {
            left = new BSTNode(driver);
        }
    } else {
        if (right != nullptr) {
            right->add(driver);
        } else {
            right = new BSTNode(driver);
        }
    }
}

Driver *BSTNode::find(unsigned int id) {
    if (id == value.driverId) return &value;
    if (id < value.driverId) {
        if (left != nullptr) {
            return left->find(id);
        }
    } else {
        if (right != nullptr) {
            return right->find(id);
        }
    }
    return nullptr;
}

void BSTNode::preorder(std::stringstream &aux) const {
    aux << value.ref;
    if (left != nullptr) {
        aux << " ";
        left->preorder(aux);
    }
    if (right != nullptr) {
        aux << " ";
        right->preorder(aux);
    }
}

void BSTNode::inorder(std::stringstream &aux, int &count, int &counter) const {
    if (count <= 0) return;
    if (left != nullptr) left->inorder(aux, count, counter);
    if (aux.tellp() != 1) aux << std::endl;
    std::string code = (value.code == "\\N" ? "" : " [" + value.code + "]");
    std::string number = (value.number == -1 ? "" : " #" + std::to_string(value.number));
    aux << counter << ". " << value.forename << " " << value.surname << code << number;
    count--;
    counter++;
    if (right != nullptr) right->inorder(aux, count, counter);
}

void BSTNode::postorder(std::stringstream &aux) const {
    if (left != nullptr) left->postorder(aux);
    if (right != nullptr) right->postorder(aux);
    if (aux.tellp() != 1) aux << " ";
    aux << value.ref;
}

void BSTNode::printlevel(std::stringstream &aux, int level) const {
    if (level == 0) {
        if (aux.tellp() != 1) aux << " ";
        aux << value.ref;
    }
    if (left != nullptr) left->printlevel(aux, level - 1);
    if (right != nullptr) right->printlevel(aux, level - 1);
}

void BSTNode::levelorder(std::stringstream &aux) const {
    int level = height();
    for (int i = 0; i < level; ++i) {
        printlevel(aux, i);
    }
}

int BSTNode::height() const {
    int leftLevel = 0, rightLevel = 0;
    if (left != nullptr) leftLevel = left->height() + 1;
    if (right != nullptr) rightLevel = right->height() + 1;
    if (leftLevel == 0 && rightLevel == 0) return 1;
    return (rightLevel > leftLevel) ? rightLevel : leftLevel;
}

bool BSTNode::ancestors(const Driver &driver, std::stringstream &aux) {
    if (driver.driverId == value.driverId) return true;
    if (driver.driverId < value.driverId) {
        if (aux.tellp() != 1) aux << " ";
        aux << value.ref;
        return (left != nullptr && left->ancestors(driver, aux));
    } else {
        if (aux.tellp() != 1) aux << " ";
        aux << value.ref;
        return (right != nullptr && right->ancestors(driver, aux));
    }
}

int BSTNode::whatLevelAmI(const Driver &driver) {
    if (driver.driverId == value.driverId) return 1;
    if (driver.driverId < value.driverId) {
        if (left != nullptr) return left->whatLevelAmI(driver) + 1;
    } else {
        if (right != nullptr) return right->whatLevelAmI(driver) + 1;
    }
    return -1;
}

class DriversBST {
private:
    BSTNode *root;
    int size;
public:
    DriversBST();

    bool isEmpty() const;

    void add(const Driver &);

    Driver *find(unsigned int &) const;

    std::string preorder() const;

    std::string inorder(int) const;

    std::string postorder() const;

    std::string levelorder() const;

    std::string visit();

    std::string ancestors(const Driver &);

    int height() const;

    int whatLevelAmI(const Driver &) const;
};

DriversBST::DriversBST() : root(nullptr), size(0) {}

bool DriversBST::isEmpty() const {
    return root == nullptr;
}

void DriversBST::add(const Driver &driver) {
    if (!isEmpty()) {
        if (!root->find(driver.driverId)) {
            root->add(driver);
        }
    } else {
        root = new BSTNode(driver);
    }
    size++;
}

Driver *DriversBST::find(unsigned int &id) const {
    if (!isEmpty()) return root->find(id);
    return nullptr;
}

std::string DriversBST::preorder() const {
    std::stringstream aux;
    aux << "[";
    if (!isEmpty()) root->preorder(aux);
    aux << "]";
    return aux.str();
}

std::string DriversBST::inorder(int count) const {
    if (count > size) {
        std::cout << "[!] No existen tantos pilotos para imprimir. (Max: " << size << ")" << std::endl;
        return "";
    }
    std::stringstream aux;
    int counter = 1;
    if (!isEmpty()) root->inorder(aux, count, counter);
    return aux.str();
}

std::string DriversBST::postorder() const {
    std::stringstream aux;
    aux << "[";
    if (!isEmpty()) root->postorder(aux);
    aux << "]";
    return aux.str();
}

std::string DriversBST::levelorder() const {
    std::stringstream aux;
    aux << "[";
    if (!isEmpty()) root->levelorder(aux);
    aux << "]";
    return aux.str();
}

std::string DriversBST::visit() {
    std::stringstream aux;
    aux << preorder() << std::endl;
    aux << inorder(size) << std::endl;
    aux << postorder() << std::endl;
    aux << levelorder();
    return aux.str();
}

std::string DriversBST::ancestors(const Driver &driver) {
    std::stringstream aux;
    aux << "[";
    if (!isEmpty()) {
        if (!root->ancestors(driver, aux)) return "[]";
    }
    aux << "]";
    return aux.str();
}

int DriversBST::height() const {
    return root->height();
}

int DriversBST::whatLevelAmI(const Driver &driver) const {
    if (!isEmpty()) {
        int lvl = root->whatLevelAmI(driver);
        if (lvl < 0) return -1;
        return lvl;
    }
    return -1;
}

#endif //INTEGRALA_DRIVERS_BST_H
