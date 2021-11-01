//
// IntegralA
//
// Ian García González
// A01706892
//
// File created on 01/11/21.
//
// Copyright © 2021. All rights reserved.
//
//

#ifndef BST_H_
#define BST_H_

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/**
 * BST: Incluye las estructuras necesarias para ejecutar el main.cpp
 * @file: bst.h
 * @author: Ian
 * */

template<class T>
class BST;

template<class T>
class Node {
private:
    T value;
    Node *left, *right;

public:
    explicit Node(T);

    Node(T, Node<T> *, Node<T> *);

    void add(T);

    bool find(T);

    void preorder(stringstream &) const;

    void inorder(stringstream &) const;

    void postorder(stringstream &) const;

    void printlevel(stringstream &, int) const;

    void levelorder(stringstream &) const;

    int height() const;

    bool ancestors(T, stringstream &);

    int whatLevelAmI(T);

    friend class BST<T>;
};

/**
 * @brief Construct a new Node< T>:: Node object
 *
 * @param val Valor del nodo.
 */
template<class T>
Node<T>::Node(T val) : value(val), left(nullptr), right(nullptr) {}

/**
 * @brief Construct a new Node< T>:: Node object
 *
 * @param val Valor del nodo.
 * @param le Nodo izquierdo.
 * @param ri Nodo derecho.
 */
template<class T>
Node<T>::Node(T val, Node<T> *le, Node<T> *ri) : value(val), left(le), right(ri) {}

/**
 * @brief Agrega un nuevo nodo.
 *
 * @param val Valor del nodo.
 */
template<class T>
void Node<T>::add(T val) {
    if (val < value) {
        if (left != nullptr) {
            left->add(val);
        } else {
            left = new Node<T>(val);
        }
    } else {
        if (right != nullptr) {
            right->add(val);
        } else {
            right = new Node<T>(val);
        }
    }
}

/**
 * @brief Encuentra si un valor está en el BST.
 *
 * @param val Valor a buscar.
 * @return true El valor fué encontrado.
 * @return false El valor no fué encontrado.
 */
template<class T>
bool Node<T>::find(T val) {
    if (val == value) return true;
    if (val < value) {
        return (left != nullptr && left->find(val));
    } else {
        return (right != nullptr && right->find(val));
    }
}

/**
 * @brief Imprime el BST en preorden.
 *
 * @param aux String.
 */
template<class T>
void Node<T>::preorder(stringstream &aux) const {
    aux << value;
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
 * @brief Imprime el BST en orden.
 *
 * @param aux String.
 */
template<class T>
void Node<T>::inorder(stringstream &aux) const {
    if (left != nullptr) left->inorder(aux);
    if (aux.tellp() != 1) aux << " ";
    aux << value;
    if (right != nullptr) right->inorder(aux);
}

/**
 * @brief Imprime el BST en postorden.
 *
 * @param aux String.
 */
template<class T>
void Node<T>::postorder(stringstream &aux) const {
    if (left != nullptr) left->postorder(aux);
    if (right != nullptr) right->postorder(aux);
    if (aux.tellp() != 1) aux << " ";
    aux << value;
}

/**
 * @brief Imprime el BST por nivel.
 *
 * @param aux String.
 * @param level Nivel a imprimir.
 */
template<class T>
void Node<T>::printlevel(stringstream &aux, int level) const {
    if (level == 0) {
        if (aux.tellp() != 1) aux << " ";
        aux << value;
    }
    if (left != nullptr) left->printlevel(aux, level - 1);
    if (right != nullptr) right->printlevel(aux, level - 1);
}

/**
 * @brief Imprime todos los niveles del BST.
 *
 * @param aux String
 */
template<class T>
void Node<T>::levelorder(stringstream &aux) const {
    int level = height();
    for (int i = 0; i < level; ++i) {
        printlevel(aux, i);
    }
}

/**
 * @brief Obtiene la profundidad del BST.
 *
 * @return int Profundidad del BST.
 */
template<class T>
int Node<T>::height() const {
    int leftLevel = 0, rightLevel = 0;
    if (left != nullptr) leftLevel = left->height() + 1;
    if (right != nullptr) rightLevel = right->height() + 1;
    if (leftLevel == 0 && rightLevel == 0) return 1;
    return (rightLevel > leftLevel) ? rightLevel : leftLevel;
}

/**
 * @brief Revisa si el nodo tiene ancestors.
 *
 * @param val Valor del nodo.
 * @param aux String
 */
template<class T>
bool Node<T>::ancestors(T val, stringstream &aux) {
    if (val == value) return true;
    if (val < value) {
        if (aux.tellp() != 1) aux << " ";
        aux << value;
        return (left != nullptr && left->ancestors(val, aux));
    } else {
        if (aux.tellp() != 1) aux << " ";
        aux << value;
        return (right != nullptr && right->ancestors(val, aux));
    }
}

/**
 * @brief Obtiene el nivel del nodo actual.
 *
 * @param val Valor del nodo.
 * @return int Nivel del nodo.
 */
template<class T>
int Node<T>::whatLevelAmI(T val) {
    if (val == value) return 1;
    if (val < value) {
        if (left != nullptr) return left->whatLevelAmI(val) + 1;
    } else {
        if (right != nullptr) return right->whatLevelAmI(val) + 1;
    }
    return -1;
}

template<class T>
class BST {
private:
    Node<T> *root;

public:
    BST();

    bool isEmpty() const;

    void add(T);

    bool find(T) const;

    string preorder() const;

    string inorder() const;

    string postorder() const;

    string levelorder() const;

    string visit();

    string ancestors(T);

    int height() const;

    int whatlevelamI(T) const;
};

/**
 * @brief Construct a new BST<T>::BST object
 */
template<class T>
BST<T>::BST() : root(nullptr) {}

/**
 * @brief Revisa si el BST está vacío.
 *
 * @return true BST está vacío.
 * @return false BST no está vacío.
 */
template<class T>
bool BST<T>::isEmpty() const {
    return root == nullptr;
}

/**
 * @brief Agrega un nuevo nodo al BST.
 *
 * @param val Valor del nuevo nodo.
 */
template<class T>
void BST<T>::add(T val) {
    if (root != nullptr) {
        if (!root->find(val)) {
            root->add(val);
        }
    } else {
        root = new Node<T>(val);
    }
}

/**
 * @brief Busca si existe algún nodo con un valor.
 *
 * @param val Valor a buscar.
 * @return true Existe el nodo.
 * @return false No existe el nodo.
 */
template<class T>
bool BST<T>::find(T val) const {
    if (root != nullptr) return root->find(val);
    return false;
}

/**
 * @brief Imprime el BST en preorden.
 *
 * @return string
 */
template<class T>
string BST<T>::preorder() const {
    stringstream aux;
    aux << "[";
    if (!isEmpty()) root->preorder(aux);
    aux << "]";
    return aux.str();
}

/**
 * @brief Imprime el BST en orden.
 *
 * @return string
 */
template<class T>
string BST<T>::inorder() const {
    stringstream aux;
    aux << "[";
    if (!isEmpty()) root->inorder(aux);
    aux << "]";
    return aux.str();
}

/**
 * @brief Imprime el BST en postorden.
 *
 * @return string
 */
template<class T>
string BST<T>::postorder() const {
    stringstream aux;
    aux << "[";
    if (!isEmpty()) root->postorder(aux);
    aux << "]";
    return aux.str();
}

/**
 * @brief Imprime el BST por niveles.
 *
 * @return string
 */
template<class T>
string BST<T>::levelorder() const {
    stringstream aux;
    aux << "[";
    if (!isEmpty()) root->levelorder(aux);
    aux << "]";
    return aux.str();
}

/**
 * @brief Imprime el BST de todas las formas posibles.
 *
 * @return string
 */
template<class T>
string BST<T>::visit() {
    stringstream aux;
    aux << preorder() << endl;
    aux << inorder() << endl;
    aux << postorder() << endl;
    aux << levelorder();
    return aux.str();
}

/**
 * @brief Imprime los ancestors de un nodo.
 *
 * @param val Valor del nodo.
 * @return string
 */
template<class T>
string BST<T>::ancestors(T val) {
    stringstream aux;
    aux << "[";
    if (!isEmpty()) {
        if (!root->ancestors(val, aux)) return "[]";
    }
    aux << "]";
    return aux.str();
}

/**
 * @brief Obtiene la altura del BST.
 *
 * @return int Altura del BST.
 */
template<class T>
int BST<T>::height() const {
    return root->height();
}

/**
 * @brief Obtiene el nivel de un nodo en específico.
 *
 * @param val Valor del nodo.
 * @return int Nivel del nodo.
 */
template<class T>
int BST<T>::whatlevelamI(T val) const {
    if (root != nullptr) {
        int lvl = root->whatLevelAmI(val);
        if (lvl < 0) return -1;
        return lvl;
    }
    return -1;
}


#endif //BST_H_
