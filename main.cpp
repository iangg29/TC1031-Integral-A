//
// IntegralA
//
// Ian García González
// A01706892
//
// File created on 20/11/21.
//
// Copyright © 2021. All rights reserved.
//
//

#include <iostream>
#include "Application.h"

Application *application = nullptr;

/**
 * @brief Iniciador de la aplicación.
 */
int main() {
    application = new Application("Formula 1 Statistics", 0.1, true);
    application->init();
}