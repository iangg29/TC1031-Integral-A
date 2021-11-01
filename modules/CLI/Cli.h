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

#ifndef INTEGRALA_CLI_H
#define INTEGRALA_CLI_H


#include <Module.h>

class CLI : public Module {
public:
    explicit CLI(Application *application) : Module(application, "CLI Handler") {};

    void start() override;

    void end() override;

    void menu() override;

    void startMenu();
};


#endif //INTEGRALA_CLI_H
