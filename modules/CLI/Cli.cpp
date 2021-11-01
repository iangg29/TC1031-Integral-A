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

#include "Application.h"
#include "Cli.h"

void CLI::start() {}

void CLI::end() {}

void CLI::menu() {}

void CLI::startMenu() {
    int option;
    do {
        getApplication()->getUtilsHandler()->log("Por favor selecciona una opción...´´", Level::INFO);
        cin >> option;
        if (option == 9){
            getApplication()->stop();
        }
    } while (getApplication()->isStarted());
}
