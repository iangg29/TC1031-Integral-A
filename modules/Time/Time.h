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

#ifndef INTEGRALA_TIME_H
#define INTEGRALA_TIME_H


#include "../../Module.h"

class Time : public Module {
public:
    explicit Time(Application *application) : Module(application, "Time Handler") {}

    void start() override;

    void end() override;

    void menu() override;

    int getMillis();
};


#endif //INTEGRALA_TIME_H
