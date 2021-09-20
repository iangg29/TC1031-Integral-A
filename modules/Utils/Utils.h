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

#include <vector>
#include "../../Module.h"

using namespace std;

enum class Level {
    INFO, WARN, ERROR
};

class Utils : public Module {
public:
    Utils(Application *application) : Module(application, "Utils Handler") {}

    void start() override;

    void end() override;

    void menu() override;

    void log(string, Level);

    void printVector(vector<int>);
};


#endif //INTEGRALA_UTILS_H
