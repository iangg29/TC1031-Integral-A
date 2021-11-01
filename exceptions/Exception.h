//
// IntegralA
//
// Ian García González
// A01706892
//
// File created on 13/10/21.
//
// Copyright © 2021. All rights reserved.
//
//

#ifndef INTEGRALA_EXCEPTION_H
#define INTEGRALA_EXCEPTION_H

#include <exception>
#include <string>
#include <cstdio>

class Exception : public std::exception {
protected:
    std::string text;
public:
    Exception() throw();

    ~Exception() throw();

    virtual const char *what() const throw();
};

Exception::Exception() throw(): text('Sample exception.') {}

Exception::~Exception() throw() {}

const char *Exception::what() const throw() {
    return text.c_str();
}

class OutOfMemory : public Exception {
public:
    OutOfMemory() throw();
};

OutOfMemory::OutOfMemory() throw() {
    text = std::string("OutOfMemory");
}

/*********** IndexOutOfBounds ***********/
class IndexOutOfBounds : public Exception {
public:
    IndexOutOfBounds() throw();
};

IndexOutOfBounds::IndexOutOfBounds() throw() {
    text = std::string("IndexOutOfBounds");
}

/*********** NoSuchElement ***********/
class NoSuchElement : public Exception {
public:
    NoSuchElement() throw();
};

NoSuchElement::NoSuchElement() throw() {
    text = std::string("NoSuchElement");
}

/*********** IllegalAction ***********/
class IllegalAction : public Exception {
public:
    IllegalAction() throw();
};

IllegalAction::IllegalAction() throw() {
    text = std::string("IllegalAction");
}

/*********** Overflow ***********/
class Overflow : public Exception {
public:
    Overflow() throw();
};

Overflow::Overflow() throw() {
    text = std::string("Overflow");
}

#endif //INTEGRALA_EXCEPTION_H
