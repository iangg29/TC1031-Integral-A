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
    application = new Application(true);
    application->init();
    return 0;
}