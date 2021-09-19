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

#include "Module.h"
#include "Application.h"

Module::Module(Application *application, string name) {
    this->application = application;
    this->name = name;
    application->addModule(this);
    try {
        start();
    } catch (exception exception) {
        logWarn("Module couldn't load.");
    }
}

Application *Module::getApplication() {
    return this->application;
}

void Module::log(const string &message) {
    cout << "[*] " << message << endl;
}

void Module::logWarn(const string &message) {
    cout << "[WARNING] " << message << endl;
}

void Module::logFatal(const string &message) {
    cout << "[ERROR] " << message << endl;
}

string Module::getName() {
    return this->name;
}

int Module::getStartupTime() const {
    return this->startupTime;
}

void Module::start() {
    if (getApplication()->isDebug()) log(getName().append(" module loaded successfully."));
}

