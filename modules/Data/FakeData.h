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

#ifndef INTEGRALA_FAKEDATA_H
#define INTEGRALA_FAKEDATA_H

#include <iostream>
#include <vector>
#include "../../Module.h"

using namespace std;

class FakeData : Module {
public:
    FakeData(Application *application) : Module(application, "Fake Data Handler") {}

    vector<int> data;

    void start() override;

    void end() override;

    void menu() override;

    void generateNewData();
};


#endif //INTEGRALA_FAKEDATA_H
