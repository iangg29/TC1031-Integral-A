//
// IntegralA
//
// Ian García González
// A01706892
//
// File created on 09/09/21.
//
// Copyright © 2021. All rights reserved.
//
//
#include "Application.h"

Application *application = nullptr;

int main() {
    application = new Application("Data Structures", true, 0.1);
    application->init();
    delete application;
    return 0;
}