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

/**
 * @brief BSTNode class
 * 
 */
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

/**
 * @brief Construct a new BSTNode::BSTNode object
 * 
 * @param driver Driver value
 */
BSTNode::BSTNode(Driver driver) : value(std::move(driver)), left(nullptr), right(nullptr) {}

/**
 * @brief Construct a new BSTNode::BSTNode object
 * 
 * @param driver Driver value
 * @param le Left node
 * @param ri Right node
 */
BSTNode::BSTNode(Driver driver, BSTNode *le, BSTNode *ri) : value(std::move(driver)), left(le), right(ri) {}

/**
 * @brief Add a new driver to the BST
 * 
 * @param driver Driver to add
 */
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

/**
 * @brief Find a driver in the BST
 * 
 * @param id Id of the driver to find
 * @return Driver* 
 */
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

/**
 * @brief Preorder traversal of the BST
 * 
 * @param aux 
 */
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

/**
 * @brief Inorder traversal of the BST
 * 
 * @param aux 
 * @param count 
 * @param counter 
 */
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

/**
 * @brief Postorder traversal of the BST
 * 
 * @param aux 
 */
void BSTNode::postorder(std::stringstream &aux) const {
    if (left != nullptr) left->postorder(aux);
    if (right != nullptr) right->postorder(aux);
    if (aux.tellp() != 1) aux << " ";
    aux << value.ref;
}

/**
 * @brief Print the BST in level order
 * 
 * @param aux 
 * @param level 
 */
void BSTNode::printlevel(std::stringstream &aux, int level) const {
    if (level == 0) {
        if (aux.tellp() != 1) aux << " ";
        aux << value.ref;
    }
    if (left != nullptr) left->printlevel(aux, level - 1);
    if (right != nullptr) right->printlevel(aux, level - 1);
}

/**
 * @brief Print the BST in level order
 * 
 * @param aux 
 */
void BSTNode::levelorder(std::stringstream &aux) const {
    int level = height();
    for (int i = 0; i < level; ++i) {
        printlevel(aux, i);
    }
}

/**
 * @brief Get the height of the BST
 * 
 * @return int 
 */
int BSTNode::height() const {
    int leftLevel = 0, rightLevel = 0;
    if (left != nullptr) leftLevel = left->height() + 1;
    if (right != nullptr) rightLevel = right->height() + 1;
    if (leftLevel == 0 && rightLevel == 0) return 1;
    return (rightLevel > leftLevel) ? rightLevel : leftLevel;
}

/**
 * @brief Get the ancestors of a driver
 * 
 * @param driver 
 * @param aux 
 * @return true 
 * @return false 
 */
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

/**
 * @brief Get the level of a node
 * 
 * @param driver 
 * @return int 
 */
int BSTNode::whatLevelAmI(const Driver &driver) {
    if (driver.driverId == value.driverId) return 1;
    if (driver.driverId < value.driverId) {
        if (left != nullptr) return left->whatLevelAmI(driver) + 1;
    } else {
        if (right != nullptr) return right->whatLevelAmI(driver) + 1;
    }
    return -1;
}

/**
 * @brief DriversBST class
 * 
 */
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

/**
 * @brief Construct a new Drivers BST:: Drivers BST object
 * 
 */
DriversBST::DriversBST() : root(nullptr), size(0) {}

/**
 * @brief Check if the BST is empty
 * 
 * @return true The BST is empty
 * @return false The BST is not empty
 */
bool DriversBST::isEmpty() const {
    return root == nullptr;
}

/**
 * @brief Add a driver to the BST
 * 
 * @param driver 
 */
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

/**
 * @brief Find a driver in the BST
 * 
 * @param id 
 * @return Driver* 
 */
Driver *DriversBST::find(unsigned int &id) const {
    if (!isEmpty()) return root->find(id);
    return nullptr;
}

/**
 * @brief Preorder traversal of the BST
 * 
 * @return std::string 
 */
std::string DriversBST::preorder() const {
    std::stringstream aux;
    aux << "[";
    if (!isEmpty()) root->preorder(aux);
    aux << "]";
    return aux.str();
}

/**
 * @brief Inorder traversal of the BST
 * 
 * @param count 
 * @return std::string 
 */
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

/**
 * @brief Postorder traversal of the BST
 * 
 * @return std::string 
 */
std::string DriversBST::postorder() const {
    std::stringstream aux;
    aux << "[";
    if (!isEmpty()) root->postorder(aux);
    aux << "]";
    return aux.str();
}

/**
 * @brief Level order traversal of the BST
 * 
 * @return std::string 
 */
std::string DriversBST::levelorder() const {
    std::stringstream aux;
    aux << "[";
    if (!isEmpty()) root->levelorder(aux);
    aux << "]";
    return aux.str();
}

/**
 * @brief Visit the BST
 * 
 * @return std::string 
 */
std::string DriversBST::visit() {
    std::stringstream aux;
    aux << preorder() << std::endl;
    aux << inorder(size) << std::endl;
    aux << postorder() << std::endl;
    aux << levelorder();
    return aux.str();
}

/**
 * @brief Get the ancestors of a driver
 * 
 * @param driver 
 * @return std::string 
 */
std::string DriversBST::ancestors(const Driver &driver) {
    std::stringstream aux;
    aux << "[";
    if (!isEmpty()) {
        if (!root->ancestors(driver, aux)) return "[]";
    }
    aux << "]";
    return aux.str();
}

/**
 * @brief Get the height of the BST
 * 
 * @return int 
 */
int DriversBST::height() const {
    return root->height();
}

/**
 * @brief Get the level of a node
 * 
 * @param driver 
 * @return int 
 */
int DriversBST::whatLevelAmI(const Driver &driver) const {
    if (!isEmpty()) {
        int lvl = root->whatLevelAmI(driver);
        if (lvl < 0) return -1;
        return lvl;
    }
    return -1;
}

#endif //INTEGRALA_DRIVERS_BST_H
