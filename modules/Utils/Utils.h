//
// IntegralA
//
// Ian García González
// A01706892
//
// File created on 18/09/21.
//
// Copyright © 2021. All rights reserved.
//
//
#ifndef INTEGRALA_UTILS_H
#define INTEGRALA_UTILS_H

#include "../../Module.h"

class Utils : public Module {
public:
    Utils(Application *application) : Module(application, "Utils Handler") {}

    void start() override;

    void end() override;

    void menu() override;
};


#endif //INTEGRALA_UTILS_H
