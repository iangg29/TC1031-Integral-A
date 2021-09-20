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

#include "Utils.h"

void Utils::start() {}

void Utils::end() {}

void Utils::menu() {}

void Utils::log(string message, Level level) {
    switch (level) {
        case Level::INFO:
            Module::log(message);
            break;
        case Level::WARN:
            Module::logWarn(message);
            break;
        case Level::ERROR:
            Module::logFatal(message);
            break;
        default:
            Module::log(message);
            break;
    }
}

void Utils::printVector(vector<int> v) {
    for(auto x : v){
        cout << x << " ";
    }
    cout << endl;
}
