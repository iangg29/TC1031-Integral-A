//
// IntegralA
//
// Ian García González
// A01706892
//
// File created on 05/10/21.
//
// Copyright © 2021. All rights reserved.
//
//

#ifndef INTEGRALA_LISTS_H
#define INTEGRALA_LISTS_H

#include "../../Module.h"

class Lists : Module {
public:
    Lists(Application *application) : Module(application, "Lists Handler") {}

    void start() override;

    void end() override;

    void menu() override;
};


#endif //INTEGRALA_LISTS_H
