//
// IntegralA
//
// Ian García González
// A01706892
//
// File created on 19/09/21.
//
// Copyright © 2021. All rights reserved.
//
//

#ifndef INTEGRALA_MODULEFAILEDLOADING_H
#define INTEGRALA_MODULEFAILEDLOADING_H

#include <iostream>
#include <exception>

class ModuleFailedLoading : public std::exception {
private:
    const char *message;

    ModuleFailedLoading();

public:
    ModuleFailedLoading(const char *s) noexcept(true): message(s) {}

    const char *what() const noexcept(true) {
        return message;
    }
};


#endif //INTEGRALA_MODULEFAILEDLOADING_H
