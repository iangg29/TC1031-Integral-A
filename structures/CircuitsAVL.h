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

#ifndef INTEGRALA_CIRCUITS_AVL_H
#define INTEGRALA_CIRCUITS_AVL_H

#include <utility>

#include "../models/Extra.h"

class CircuitsAVL;

class Node {
private:
    Circuit value;
    Node *left, *right;
    int level, balance;

    Node *predecesor();

public:
    explicit Node(Circuit);

    Node(Circuit, Node *, Node *, int, int);

    void add(const Circuit &);

    bool find(int);

    void remove(int);

    void removeChilds();

    void inorder(std::stringstream &, int &, int &) const;

    void preorder(std::stringstream &) const;

    int max_depth();

    Node *check_tree(Circuit *, Node *, bool *);

    Node *balance_tree();

    static Node *rot_left(Node *);

    static Node *rot_right(Node *);

    static Node *rot_left_right(Node *);

    static Node *rot_right_left(Node *);

    friend class CircuitsAVL;
};

Node::Node(Circuit circuit) : value(std::move(circuit)), left(nullptr), right(nullptr), level(0), balance(0) {}

Node::Node(Circuit circuit, Node *le, Node *ri, int lvl, int bal) : value(std::move(circuit)), left(le), right(ri),
                                                                    level(lvl),
                                                                    balance(bal) {}

void Node::add(const Circuit &circuit) {
    if (circuit.circuitId < value.circuitId) {
        if (left != nullptr) {
            left->add(circuit);
        } else {
            left = new Node(circuit);
        }
    } else {
        if (right != nullptr) {
            right->add(circuit);
        } else {
            right = new Node(circuit);
        }
    }
}

bool Node::find(int id) {
    if (id == value.circuitId) {
        return true;
    } else if (id < value.circuitId) {
        return (left != nullptr && left->find(id));
    } else if (id > value.circuitId) {
        return (right != nullptr && right->find(id));
    }
    return false;
}

Node *Node::predecesor() {
    Node *le, *ri;
    le = left;
    ri = right;

    if (left == nullptr) {
        if (right != nullptr) {
            right = nullptr;
        }
        return ri;
    }

    if (left->right == nullptr) {
        left = left->left;
        le->left = nullptr;
        return le;
    }

    Node *parent, *child;
    parent = left;
    child = left->right;
    while (child->right != nullptr) {
        parent = child;
        child = child->right;
    }
    parent->right = child->left;
    child->left = nullptr;
    return child;
}

void Node::remove(int id) {
    Node *succ, *old;
    if (id < value.circuitId) {
        if (left != nullptr) {
            if (left->value.circuitId == id) {
                old = left;
                succ = left->predecesor();
                if (succ != nullptr) {
                    succ->left = old->left;
                    succ->right = old->right;
                }
                left = succ;
                delete old;
            } else {
                left->remove(id);
            }
        }
    } else if (id > value.circuitId) {
        if (right != nullptr) {
            if (right->value.circuitId == id) {
                old = right;
                succ = right->predecesor();
                if (succ != nullptr) {
                    succ->left = old->left;
                    succ->right = old->right;
                }
                right = succ;
                delete old;
            } else {
                right->remove(id);
            }
        }
    }
}

void Node::removeChilds() {
    if (left != nullptr) {
        left->removeChilds();
        delete left;
        left = nullptr;
    }
    if (right != nullptr) {
        right->removeChilds();
        delete right;
        right = nullptr;
    }
}

void Node::inorder(std::stringstream &aux, int &count, int &counter) const {
    if (count <= 0) return;
    if (left != nullptr) left->inorder(aux, count, counter);
    if (count <= 0) return;
    if (aux.tellp() != 1) aux << std::endl;
    if (count <= 0) return;
    aux << counter << ". " << value.name << " (" << value.location << ", " << value.country << ")";
    count--;
    counter++;
    if (count <= 0) return;
    if (right != nullptr) right->inorder(aux, count, counter);
}

void Node::preorder(std::stringstream &aux) const {
    aux << "(" << value.name << " " << level << " " << balance << ")";
    if (left != nullptr) {
        aux << " ";
        left->preorder(aux);
    }
    if (right != nullptr) {
        aux << " ";
        right->preorder(aux);
    }
}

int Node::max_depth() {
    int le = 0, ri = 0;
    if (left != nullptr)
        le = left->max_depth() + 1;
    if (right != nullptr)
        ri = right->max_depth() + 1;
    if (le > ri)
        level = le;
    else
        level = ri;
    balance = le - ri;
    return level;
}

Node *Node::check_tree(Circuit *circuit, Node *parent, bool *checked) {
    Node *le = nullptr, *ri = nullptr, *a = nullptr;
    if (left != nullptr)
        le = left->check_tree(circuit, this, checked);
    if (right != nullptr)
        ri = right->check_tree(circuit, this, checked);
    if (!*checked) {
        if (balance > 1) {
            a = balance_tree();
            *circuit = value;
            *checked = true;
            if (parent != nullptr) {
                parent->left = a;
            }
        } else if (balance < -1) {
            a = balance_tree();
            *circuit = value;
            *checked = true;
            if (parent != nullptr) {
                parent->right = a;
            }
        }
    }
    return a;
}

Node *Node::balance_tree() {
    Node *a = this, *le = left, *ri = right;
    if (balance > 0) {
        if (le->balance > 0) {
            a = rot_right(a);
        } else {
            a = rot_left_right(a);
        }
    } else {
        if (ri->balance < 0) {
            a = rot_left(a);
        } else {
            a = rot_right_left(a);
        }
    }
    return a;
}

Node *Node::rot_left(Node *a) {
    Node *b, *temp = nullptr;
    if (a->right != nullptr) {
        b = a->right;
        if (b->left != nullptr)
            temp = b->left;
        b->left = a;
        if (temp != nullptr) {
            a->right = temp;
        } else {
            a->right = nullptr;
        }
    }
    return b;
}

Node *Node::rot_right(Node *a) {
    Node *b, *temp = nullptr;
    if (a->left != nullptr) {
        b = a->left;
        if (b->right != nullptr)
            temp = b->right;
        b->right = a;
        if (temp != nullptr) {
            a->left = temp;
        } else {
            a->left = nullptr;
        }
    }
    return b;
}

Node *Node::rot_left_right(Node *a) {
    a->left = rot_left(a->left);
    a = rot_right(a);
    return a;
}

Node *Node::rot_right_left(Node *a) {
    a->right = rot_right(a->right);
    a = rot_left(a);
    return a;
}

class CircuitsAVL {
private:
    Node *root;
    int size;
public:
    CircuitsAVL();

    ~CircuitsAVL();

    bool empty() const;

    void add(const Circuit &);

    bool find(int) const;

    void remove(int);

    void removeAll();

    std::string inorder(int) const;

    std::string preorder() const;
};

CircuitsAVL::CircuitsAVL() : root(nullptr), size(0) {}

CircuitsAVL::~CircuitsAVL() {
    removeAll();
}

bool CircuitsAVL::empty() const {
    return root == nullptr;
}

void CircuitsAVL::add(const Circuit &circuit) {
    if (!empty()) {
        if (!root->find(circuit.circuitId)) {
            Node *temp;
            Circuit check_val(circuit);
            bool aux = false;
            root->add(circuit);
            root->max_depth();
            temp = root->check_tree(&check_val, nullptr, &aux);
            if (check_val.circuitId == root->value.circuitId) {
                root = temp;
            }
            root->max_depth();
        }
    } else {
        root = new Node(circuit);
    }
    size++;
}

bool CircuitsAVL::find(int id) const {
    if (!empty()) {
        return root->find(id);
    } else {
        return false;
    }
}

void CircuitsAVL::remove(int id) {
    if (!empty()) {
        if (id == root->value.circuitId) {
            Node *succ = root->predecesor();
            if (succ != nullptr) {
                succ->left = root->left;
                succ->right = root->right;
            }
            delete root;
            root = succ;
        } else {
            root->remove(id);
        }
        root->max_depth();
        Node *temp;
        Circuit check_val;
        bool aux = false;
        temp = root->check_tree(&check_val, nullptr, &aux);
        if (check_val.circuitId == root->value.circuitId) {
            root = temp;
        }
        root->max_depth();
    }
}

void CircuitsAVL::removeAll() {
    if (!empty()) {
        root->removeChilds();
    }
    delete root;
    root = nullptr;
}

std::string CircuitsAVL::inorder(int count) const {
    if (count > size) {
        std::cout << "[!] No existen tantos circuitos para imprimir. (Max: " << size << ")" << std::endl;
        return "";
    }
    std::stringstream aux;
    int counter = 1;
    if (!empty()) {
        root->inorder(aux, count, counter);
    }
    return aux.str();
}

std::string CircuitsAVL::preorder() const {
    std::stringstream aux;
    aux << "[";
    if (!empty()) {
        root->preorder(aux);
    }
    aux << "]";
    return aux.str();
}

#endif //INTEGRALA_CIRCUITS_AVL_H
